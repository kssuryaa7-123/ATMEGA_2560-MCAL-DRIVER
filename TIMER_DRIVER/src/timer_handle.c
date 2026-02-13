/*----------------------------------------------------------
 * File    : timer_handle.c
 * Purpose : Timer handle configuration logic for ATmega2560
 *
 * This file contains internal helper functions used to
 * configure blocking and non-blocking timer handles.
 *
 * Scope   : Internal to TIMER MCAL driver
 *----------------------------------------------------------*/

#include "timer_handle.h"
#include "timer_driver.h"
#include <math.h>


//==================================================
// Global Variables...
//==================================================
uint32_t micro_sec_delay = 0;

timer_handle_t block_handle;
timer_handle_t non_block_handle;


//==================================================
// Internal Helper Function Prototypes...
//==================================================
void     select_timer(timer_handle_t *h, uint32_t value_us);
void     select_prescalar_val(timer_handle_t *h, uint32_t value_us);
float    total_ticks(timer_handle_t *h, uint32_t value_us);
uint32_t converted_ticks(timer_handle_t *h, float ticks);
void     calc_ocr_value_and_cycle(timer_handle_t *h, uint32_t ticks);


//----------------------------------------------------------
/* Function : time_to_microsec
 * Purpose  : Convert time value to microseconds
 * Input    : value - Time value
 *            unit  - Time unit (MILLI_SEC / MICRO_SEC / SEC)
 * Return   : Time in microseconds
 *----------------------------------------------------------*/
uint32_t time_to_microsec(uint32_t value, time_unit_t unit)
{
    if (unit == MILLI_SEC)
    {
        return value * 1000UL;
    } 
    else if (unit == SEC)
    {
        return value * 1000000UL;
    }
    else
    {
        return value;   // MICRO_SEC
    }
}


//----------------------------------------------------------
/* Function : select_timer
 * Purpose  : Select appropriate timer based on delay type
 * Input    : h        - Timer handle pointer
 *            value_us - Time in microseconds
 *----------------------------------------------------------*/
void select_timer(timer_handle_t *h, uint32_t value_us)
{
    if (h->type == TIMER_BLOCKING)
    {
        if (value_us < 16384U)
        {
            h->timer = TIMER0;   // 8-bit timer
        }
        else
        {
            h->timer = TIMER1;   // 16-bit timer
        }
    }
    else
    {
        h->timer = TIMER3;       // Non-blocking uses Timer 3
    }
}


//----------------------------------------------------------
/* Function : select_prescalar_val
 * Purpose  : Select prescaler based on delay requirement
 * Input    : h        - Timer handle pointer
 *            value_us - Time in microseconds
 *----------------------------------------------------------*/
void select_prescalar_val(timer_handle_t *h, uint32_t value_us)
{
    if (h->type == TIMER_BLOCKING)
    {
        if (h->timer == TIMER0)
        {
            if (value_us <= 16U)
                h->prescaler = PRESCALER_1;
            else if (value_us <= 128U)
                h->prescaler = PRESCALER_8;
            else if (value_us <= 1024U)
                h->prescaler = PRESCALER_64;
            else if (value_us <= 4096U)
                h->prescaler = PRESCALER_256;
            else
                h->prescaler = PRESCALER_1024;
        }
        else if (h->timer == TIMER1)
        {
            if (value_us <= 4096U)
                h->prescaler = PRESCALER_1;
            else if (value_us <= 32768U)
                h->prescaler = PRESCALER_8;
            else if (value_us <= 262144U)
                h->prescaler = PRESCALER_64;
            else if (value_us <= 1048576U)
                h->prescaler = PRESCALER_256;
            else
                h->prescaler = PRESCALER_1024;
        }
    }
    else
    {
        if (value_us <= 4096U)
            h->prescaler = PRESCALER_1;
        else if (value_us <= 32768U)
            h->prescaler = PRESCALER_8;
        else if (value_us <= 262144U)
            h->prescaler = PRESCALER_64;
        else if (value_us <= 1048576U)
            h->prescaler = PRESCALER_256;
        else
            h->prescaler = PRESCALER_1024;
    }
}


//----------------------------------------------------------
/* Function : total_ticks
 * Purpose  : Calculate total timer ticks required
 * Input    : h        - Timer handle pointer
 *            value_us - Time in microseconds
 * Return   : Total ticks as floating-point value
 *----------------------------------------------------------*/
float total_ticks(timer_handle_t *h, uint32_t value_us)
{
    /* F_CPU = 16 MHz → 16 ticks per microsecond */
    return ((value_us * 16.0f) / h->prescaler);
}


//----------------------------------------------------------
/* Function : converted_ticks
 * Purpose  : Convert float ticks to integer ticks
 * Input    : h     - Timer handle pointer
 *            ticks - Calculated tick value
 * Return   : Rounded / ceiled tick count
 *----------------------------------------------------------*/
uint32_t converted_ticks(timer_handle_t *h, float ticks)
{
    if (h->type == TIMER_BLOCKING)
    {
        if (h->timer == TIMER0)
        {
            return (uint32_t)ceil(ticks);
        }
        else
        {
            return (uint32_t)round(ticks);
        }
    }
    else
    {
        return (uint32_t)round(ticks);
    }
}


//----------------------------------------------------------
/* Function : calc_ocr_value_and_cycle
 * Purpose  : Compute OCR values and timer cycles
 * Input    : h     - Timer handle pointer
 *            ticks - Total tick count
 *----------------------------------------------------------*/
void calc_ocr_value_and_cycle(timer_handle_t *h, uint32_t ticks)
{
    if (h->type == TIMER_BLOCKING)
    {
        if ((h->timer == TIMER1) &&
            (h->prescaler == PRESCALER_1024) &&
            (ticks > TIMER1_MAX_TICKS))
        {
            uint32_t full_cycles = ticks / TIMER1_MAX_TICKS;
            uint32_t remaining   = ticks % TIMER1_MAX_TICKS;

            h->cycles = full_cycles;
            h->ocr_value16 = (uint16_t)(TIMER1_MAX_TICKS - 1U);

            if (remaining != 0U)
            {
                h->partial_cycle = 1U;
                h->partial_ocr16 = (uint16_t)(remaining - 1U);
            }
            else
            {
                h->partial_cycle = 0U;
                h->partial_ocr16 = 0U;
            }
        }
        else
        {
            h->cycles = 1U;
            h->partial_cycle = 0U;
            h->partial_ocr16 = 0U;

            if (h->timer == TIMER0)
                h->ocr_value8 = (uint8_t)(ticks - 1U);
            else
                h->ocr_value16 = (uint16_t)(ticks - 1U);
        }
    }
    else
    {
        if ((ticks > TIMER3_MAX_TICKS) &&
            (h->prescaler == PRESCALER_1024))
        {
            uint32_t full_cycles = ticks / TIMER3_MAX_TICKS;
            uint32_t remaining   = ticks % TIMER3_MAX_TICKS;

            h->cycles = full_cycles;
            h->ocr_value16 = (uint16_t)(TIMER3_MAX_TICKS - 1U);

            if (remaining != 0U)
            {
                h->partial_cycle = 1U;
                h->partial_ocr16 = (uint16_t)(remaining - 1U);
            }
            else
            {
                h->partial_cycle = 0U;
                h->partial_ocr16 = 0U;
            }
        }
        else
        {
            h->cycles = 1U;
            h->partial_cycle = 0U;
            h->partial_ocr16 = 0U;
            h->ocr_value16   = (uint16_t)(ticks - 1U);
        }
    }
}


//----------------------------------------------------------
/* Function : timer_block_handle_config
 * Purpose  : Configure blocking timer handle
 * Input    : h        - Timer handle pointer
 *            value_us - Time in microseconds
 *----------------------------------------------------------*/
void timer_block_handle_config(timer_handle_t *h, uint32_t value_us)
{
    float ticks;
    uint32_t final_ticks;

    h->type = TIMER_BLOCKING;

    select_timer(h, value_us);
    select_prescalar_val(h, value_us);

    ticks = total_ticks(h, value_us);
    final_ticks = converted_ticks(h, ticks);

    calc_ocr_value_and_cycle(h, final_ticks);
}


//----------------------------------------------------------
/* Function : timer_non_block_handle_config
 * Purpose  : Configure non-blocking timer handle
 * Input    : h        - Timer handle pointer
 *            value_us - Time in microseconds
 *----------------------------------------------------------*/
void timer_non_block_handle_config(timer_handle_t *h, uint32_t value_us)
{
    float ticks;
    uint32_t final_ticks;

    h->type = TIMER_NON_BLOCKING;

    select_timer(h, value_us);
    select_prescalar_val(h, value_us);

    ticks = total_ticks(h, value_us);
    final_ticks = converted_ticks(h, ticks);

    calc_ocr_value_and_cycle(h, final_ticks);
}


//----------------------------------------------------------
/* Function : timer_non_block_handle_reset
 * Purpose  : Reset non-blocking timer handle
 * Input    : h - Timer handle pointer
 *----------------------------------------------------------*/
void timer_non_block_handle_reset(timer_handle_t *h)
{
    h->timer          = TIMER3;
    h->prescaler      = PRESCALER_NONE;
    h->cycles         = 0U;
    h->partial_cycle  = 0U;
    h->ocr_value16    = 0U;
    h->partial_ocr16  = 0U;
    h->callback       = 0;
}

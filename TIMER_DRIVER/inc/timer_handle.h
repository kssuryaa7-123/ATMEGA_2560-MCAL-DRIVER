#ifndef TIMER_HANDLE_H
#define TIMER_HANDLE_H

/*==========================================================
 * File   : timer_handle.h
 * Brief  : Timer handle definitions for ATmega2560
 *
 * This file defines all timer-related data types, enums,
 * and handle structures used internally by the timer driver.
 *
 * Design:
 *  - MCAL-style abstraction
 *  - Handle-based configuration
 *  - Supports blocking and non-blocking timers
 *==========================================================*/

#include <stdint.h>
#include "Atmega_2560_timer_regdef.h"


//================================
 // Timer Hardware Limits...
 //================================
#define TIMER0_MAX_TICKS   256U
#define TIMER1_MAX_TICKS   65536U
#define TIMER3_MAX_TICKS   65536U


//===========================
// Time Unit Definition...
//===========================
typedef enum
{
  MILLI_SEC = 0U,
  MICRO_SEC,
  SEC
} time_unit_t;



//===================================
// Timer Instance Identification...
//===================================
typedef enum
{
  TIMER0 = 0U, //for blocking delay
  TIMER1 = 1U, //for blocking delay
  TIMER3 = 3U //FOR NON BLOCKING DELAY
} timer_identify_t;


//============================
// Timer Prescaler Values...
//============================
typedef enum
{
  PRESCALER_NONE = 0U,
  PRESCALER_1 = 1U,
  PRESCALER_8 = 8U,
  PRESCALER_64 = 64U,
  PRESCALER_256 = 256U,
  PRESCALER_1024 = 1024U,
} timer_prescaler_t;


//==========================
// Timer Operating TYPE...
//==========================
typedef enum
{
  TIMER_BLOCKING = 0U, 
  TIMER_NON_BLOCKING
} timer_type_t;



//===============================================
// Timer Callback Type (For ISR-based timer - 3)...
 //==============================================
typedef void (*timer_callback_t)(void);



//===========================
// Timer Handle Structure...
//===========================
typedef struct
{
    timer_identify_t   timer;        // TIMER0, TIMER1, TIMER3..   
    timer_prescaler_t  prescaler;        // Prescaler selection..         
    timer_type_t       type;             // Blocking / Non-blocking..     

    uint32_t           cycles;           // Full compare-match cycles..     
    uint8_t            partial_cycle;      // Partial cycle flag..            

    uint8_t            ocr_value8;       // OCR value for 8-bit timer..     
    uint16_t           ocr_value16;      // OCR value for 16-bit timer..    
    uint16_t           partial_ocr16;   // Partial OCR for last cycle..    

    timer_callback_t   callback;         // ISR callback (non-blocking)..   

} timer_handle_t;



//==============================================
// Internal Driver Handles (NOT user-facing)...
//==============================================
extern timer_handle_t block_handle;
extern timer_handle_t non_block_handle;



//========================
// Utility Functions...
//========================

//convert time value to microsecond..
uint32_t time_to_microsec(uint32_t value,time_unit_t unit);



//============================================               
// Handle Configuration APIs (Internal Use)...
//=============================================

// Configure blocking timer handle based on time in microseconds..
void timer_block_handle_config(timer_handle_t *handle,uint32_t time_us);

// Configure non-blocking timer handle based on time in microseconds..
void timer_non_block_handle_config(timer_handle_t *handle,uint32_t time_us);

// Reset non-blocking timer handle to default state..
void timer_non_block_handle_reset(timer_handle_t *handle);

#endif // TIMER_HANDLE_H..

#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

/*==========================================================
 * File    : timer_driver.h
 * Brief   : Timer driver interface for ATmega2560
 *
 * Provides blocking delay and non-blocking timer services
 * using hardware timers in CTC mode.
 *
 * Layer   : MCAL
 *==========================================================*/

#include <avr/interrupt.h>
#include "timer_handle.h"

//==========================================================
//Public Timer Driver APIs
//==========================================================


/*----------------------------------------------------------
 * Function : timer_delay
 * Purpose  : Generate a blocking delay using hardware timer
 *
 * Params   : value -> delay value
 *            unit  -> time unit (us / ms / sec)
 *
 * Notes    :
 *  - Function blocks execution until delay expires
 *  - Suitable for simple delays (not ISR-safe)
 *----------------------------------------------------------*/
void timer_delay(uint32_t value, time_unit_t unit);



/*----------------------------------------------------------
 * Function : TIMER_INIT
 * Purpose  : Initialize non-blocking timer with callback
 *
 * Params   : value -> timer period
 *            unit  -> time unit (us / ms / sec)
 *            cb    -> callback function executed on expiry
 *
 * Notes    :
 *  - Callback is executed in ISR context
 *  - Callback must be short and non-blocking
 *----------------------------------------------------------*/
void TIMER_INIT(uint32_t value, time_unit_t unit, timer_callback_t cb);




/*----------------------------------------------------------
 * Function : TIMER_START
 * Purpose  : Start non-blocking timer operation
 *
 * Notes    :
 *  - TIMER_INIT() must be called before this function
 *----------------------------------------------------------*/
void TIMER_START(void);




/*----------------------------------------------------------
 * Function : TIMER_STOP
 * Purpose  : Stop non-blocking timer
 *
 * Notes    :
 *  - Timer counter is reset
 *----------------------------------------------------------*/
void TIMER_STOP(void);




/*----------------------------------------------------------
 * Function : TIMER_DEINIT
 * Purpose  : De-initialize non-blocking timer
 *
 * Notes    :
 *  - Disables timer hardware
 *  - Clears internal driver state
 *----------------------------------------------------------*/
void TIMER_DEINIT(void);




#endif // TIMER_DRIVER_H 

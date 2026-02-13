
#include "timer_driver.h"
  

  void timer_delay(uint32_t value, time_unit_t unit)
  {
    uint32_t micro_sec_delay = time_to_microsec(value, unit);//conver the given unit to standard microsecond unit for timer hardware

    timer_block_handle_config(&block_handle, micro_sec_delay); //exactly calcuktes ,timer,prescale and ocr values and its cycles

    timer_hardware_reset(&block_handle);// always reset the hardware before the reset..
    set_ctc_mode(&block_handle);// set timers to the ctc mode by default..
    set_ocr_value(&block_handle);// SET OCR values based on the timer
    timer_start(&block_handle);//start the timer(0/1)

    wait_and_stop_timer(&block_handle);// wait until the selecfted timer compare match
  }



  void TIMER_INIT(uint32_t value, time_unit_t unit, timer_callback_t cb)
  {
    sei();//enable global interrupt....

    non_block_handle.callback = cb; // store the entered function address in structure
    uint32_t micro_sec_delay =  time_to_microsec(value, unit);
    timer_non_block_handle_config(&non_block_handle, micro_sec_delay);
    timer_hardware_reset(&non_block_handle);//always ensure the to start with 0;
    set_ctc_mode(&non_block_handle);// set timers to the ctc mode by default..
    set_ocr_value(&non_block_handle);// SET OCR values based on the timer
    set_mask_flag(&non_block_handle);//set the timer interrupt mask flag..
  }


  void TIMER_START(void)// start based on the prescale value
  {
    timer_handle_t *h = &non_block_handle;
    set_prescale(h);
  }



  void TIMER_STOP(void)
  {

    TCCR3B &= ~((1 << CS30) | (1 << CS31) | (1 << CS32)); //TURN OFF CLOCK FOR TIMER3;
    timer_reset_counter(&non_block_handle);
  }


  void TIMER_DEINIT(void)
  {
    timer_hardware_reset(&non_block_handle);// FULL TIMER3 HARDWARE RESET
    timer_non_block_handle_reset(&non_block_handle);//full handle reset;
  }



/*==============================================================================
    Supporting Function Prototypes
==============================================================================*/

//driver supporting functions...

void set_prescale(timer_handle_t*);

void set_ctc_mode(timer_handle_t*);

void set_ocr_value(timer_handle_t*);

void set_partial_ocr_value(timer_handle_t*);

void set_mask_flag(timer_handle_t*);

void handle_flag_timer0(timer_handle_t*);
void handle_flag_timer1(timer_handle_t*);
void handle_partial_cycles_timer1(timer_handle_t*);

void timer_reset_counter(timer_handle_t *);// used in  stop the timer function ;

void timer_hardware_reset(timer_handle_t *);

void timer_start(timer_handle_t*);//for blocking delay;
void timer_stop(timer_handle_t*);//for blocking delay;

void wait_and_stop_timer(timer_handle_t*);// wait until the ooverflow flag is set to achiebe the required delay..

//-------------------------------------------------------------------------------------------------------------------------


/*==============================================================================
    Timer Start / Stop
==============================================================================*/

void timer_start(timer_handle_t* h)
{
    set_prescale(h);
}

void timer_stop(timer_handle_t* h)
{
  if (h-> timer == TIMER0)
  {
    TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));// JUST TURN OFF THE CLOCK OF THE TIMER 0
  }
  else //if (block_handle.timer == TIMER1) //if timer1 is choosed..
  {
    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12)); //TURN OFF CLOCK FOR TIMER1;
  }

  timer_reset_counter(h);
}



/*==============================================================================
    Prescaler Configuration
==============================================================================*/

void set_prescale(timer_handle_t* h)
{
    if (h->type == TIMER_BLOCKING)
    {
        /* ================= TIMER 0 ================= */
        if (h->timer == TIMER0)
        {
            /* Clear prescaler bits */
            TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));

            switch (h->prescaler)
            {
                case PRESCALER_1:
                    TCCR0B |= (1 << CS00);
                    break;

                case PRESCALER_8:
                    TCCR0B |= (1 << CS01);
                    break;

                case PRESCALER_64:
                    TCCR0B |= (1 << CS00) | (1 << CS01);
                    break;

                case PRESCALER_256:
                    TCCR0B |= (1 << CS02);
                    break;

                case PRESCALER_1024:
                    TCCR0B |= (1 << CS00) | (1 << CS02);
                    break;

                default:
                    /* Invalid prescaler - optional error handling */
                    break;
            }
        }

        /* ================= TIMER 1 ================= */
        else
        {
            TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));

            switch (h->prescaler)
            {
                case PRESCALER_1:
                    TCCR1B |= (1 << CS10);
                    break;

                case PRESCALER_8:
                    TCCR1B |= (1 << CS11);
                    break;

                case PRESCALER_64:
                    TCCR1B |= (1 << CS10) | (1 << CS11);
                    break;

                case PRESCALER_256:
                    TCCR1B |= (1 << CS12);
                    break;

                case PRESCALER_1024:
                    TCCR1B |= (1 << CS10) | (1 << CS12);
                    break;

                default:
                    break;
            }
        }
    }

    /* ================= TIMER 3 (NON-BLOCKING) ================= */
    else
    {
        TCCR3B &= ~((1 << CS30) | (1 << CS31) | (1 << CS32));

        switch (h->prescaler)
        {
            case PRESCALER_1:
                TCCR3B |= (1 << CS30);
                break;

            case PRESCALER_8:
                TCCR3B |= (1 << CS31);
                break;

            case PRESCALER_64:
                TCCR3B |= (1 << CS30) | (1 << CS31);
                break;

            case PRESCALER_256:
                TCCR3B |= (1 << CS32);
                break;

            case PRESCALER_1024:
                TCCR3B |= (1 << CS30) | (1 << CS32);
                break;

            default:
                break;
        }
    }
}


  void set_mask_flag(timer_handle_t* h)
  {
    if (h-> timer == TIMER3)
    {
      TIMSK3 |= (1 << OCIE3A);// SET the interrupt mask register
    }
  }


//=========================
//    Hardware Reset...
//=========================
  void timer_hardware_reset(timer_handle_t * h)
  {
    if (h-> type == TIMER_BLOCKING)
    {
      if (h-> timer == TIMER0)
      {
        TCCR0A = 0;// set timer control registerA to zero..
        TCCR0B = 0; // SET TIMER CONTROL STATUS REGISTER B TO ZERO..
        TCCR0B = 0;
        TCNT0  = 0;//initialize the counter register to zero

        TIFR0 |= (1 << OCF0A);   // clear compare flag
        TIMSK0 = 0;             // disable interrupts
        OCR0A = 0; //set OCR value to zero
      }
      else //if (ctc_handle.timer == 1) //timer1 is choosed
      {
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1H = 0;
        TCNT1L = 0;

        TIFR1 |= (1 << OCF1A);// TURN OFF THE FLAG REGISTER
        TIMSK1 = 0;  // DISABLE THe mak register
        OCR1AH = 0;// set higher OCR value to zero
        OCR1AL = 0;// set lower OCR vslue to zero
      }
    }

    else//non-blocking
    {
      TCCR3A = 0;
      TCCR3B = 0;
      TCNT3H = 0;
      TCNT3L = 0;

      TIFR3 |= (1 << OCF3A);// TURN OFF THE FLAG REGISTER
      TIMSK3 = 0;  // DISABLE THe mak register
      OCR3AH = 0;// set higher OCR value to zero
      OCR3AL = 0;// set lower OCR vslue to zero
    }
  }


//======================
//   Counter Reset...
//=======================
  void timer_reset_counter(timer_handle_t * h)
  {
    if (h-> type == TIMER_BLOCKING)
    {
      if (h-> timer == TIMER0)
      {
        TCNT0  = 0;//initialize the counter register to zero
      }
      else //if (ctc_handle.timer == TIMER1) //default point to 16 bit timer..
      {
        TCNT1H = 0;
        TCNT1L = 0;
      }
    }

    else//non blocking
    {
      TCNT3H = 0;
      TCNT3L = 0;
    }
  }


//=================
//    CTC Mode...
//==================
  void set_ctc_mode(timer_handle_t * h)
  {
    if (h-> type == TIMER_BLOCKING)
    {
      if (h-> timer == TIMER0)
      {
        TCCR0A |= (1 << WGM01);// set the 8 bit timer in the ctc mode.
      }
      else// if (block_handle.timer == TIMER1) //timer1 selected
      {
        TCCR1B |= (1 << WGM12);// set 16 bit timer in the ctc mode.
      }
    }
    else//non_blocking
    {
      TCCR3B |= (1 << WGM32);// set 16 bit timer3 in the ctc mode.
    }
  }


//----------------------------------------------------------------------------------
//==========================
//    OCR Configuration...
//==========================
  void set_ocr_value(timer_handle_t * h)
  {
    if (h-> type == TIMER_BLOCKING)
    {
      if (h-> timer == TIMER0)
      {
        OCR0A = h-> ocr_value8; // map the calculated 8 bit value to the ocr register..
      }
      else// if (ctc_handle.timer == TIMER1) //if timer1 CHOOSED
      {
        OCR1AH = (h-> ocr_value16 >> 8); //set the higher ocr bytes value...
        OCR1AL = (h-> ocr_value16 & 0xFF);//set the lower ocr bytes value...
      }
    }

    else//non-blocking
    {
      OCR3AH = (h-> ocr_value16 >> 8); //set the higher ocr bytes value...
      OCR3AL = (h-> ocr_value16 & 0xFF);//set the lower ocr bytes value..
    }
  }



  void set_partial_ocr_value(timer_handle_t * h)
  {
    if (h-> type == TIMER_BLOCKING)
    {
      if (h-> timer == TIMER1)
      {
        OCR1AH = (h-> partial_ocr16 >> 8); //set the higher ocr bytes value...
        OCR1AL = (h-> partial_ocr16 & 0xFF);//set the lower ocr bytes value...
      }
    }

    else//non blocking
    {
      OCR3AH = (h-> partial_ocr16 >> 8); //set the higher ocr bytes value...
      OCR3AL = (h-> partial_ocr16 & 0xFF);//set the lower ocr bytes value...
    }
  }

//---------------------------------------------------------------------------------


//=================================
//    Blocking Flag Handling...
//=================================
  void handle_flag_timer0(timer_handle_t* h)
  {
    while (!(TIFR0 & (1 << OCF0A)))// wait until 8 bit timer flag is set...
    {
      //WAIT TILL THE CYCLE FINISHES TO REACH THE DESIRED COUNT..
    }
    TIFR0 |= (1 << OCF0A); //clear the 8 bit flag bit after it set...
    timer_stop(h);// then stop the timer..
  }


  void handle_flag_timer1(timer_handle_t* h)
  {
    while (!(TIFR1 & (1 << OCF1A)))//wait until the 16bit timer flag is set
    {
      //WAIT TILL THE CYCLE FINISHES TO REACH THE DESIRED COUNT..
    }
    TIFR1 |= (1 << OCF1A); //clear the 8 bit flag bit after it set...
    timer_stop(h);// then stop the timer..
  }


  void handle_partial_cycles_timer1(timer_handle_t* h)
  {
    timer_stop(h);
    set_partial_ocr_value(h);//mnow set the partial value to the 16bit ocr register..
    timer_start(h);//again start the timer
    handle_flag_timer1(h);//check the flag and exit.
  }


  void wait_and_stop_timer(timer_handle_t* h)
  {
    uint32_t cycles = h-> cycles;
    uint32_t i;

    if (h-> timer == TIMER0) // if the user select the timer 0;
    {
      handle_flag_timer0(h);
    }

    else//then default value set as timer 1(16-bit)
    {
      //condition used to check if it is 16 bit and if it has partial cycle..
      if ((h-> timer == TIMER1) && (h-> partial_cycle == 1))
      { //this blog run the full cycle of the overflow
        for (i = 1; i <= cycles; i++)
        {
          while (!(TIFR1 & (1 << OCF1A))) //wait until the 16bit timer flag is set
          {
            //WAIT TILL THE CYCLE FINISHES TO REACH THE DESIRED COUNT..
          }
          TIFR1 |= (1 << OCF1A); //clear the 8 bit flag bit after it set...
        }
        //this block runs the partial value to load in the overflow.
        handle_partial_cycles_timer1(h);
      }

      else
      {
        handle_flag_timer1(h);
      }
    }
  }

//----------------------------------------------------------------------------------


//=================================
//    INTERUUPT ISR HANDLING...
//=================================
  ISR(TIMER3_COMPA_vect)
  {
    timer_handle_t *h = &non_block_handle;

    if ((h-> cycles == 1) && (h-> partial_cycle == 0))
    {
      h-> callback();
    }

    else if ((h-> cycles == 1) && (h-> partial_cycle == 1))
    {
      static uint8_t count = 0;
      if (count < 1)
      {
        timer_reset_counter(h);
        set_partial_ocr_value(h);
        count = 1;
      }

      else
      {
        timer_reset_counter(h);
        set_ocr_value(h);
        count = 0;
        h-> callback();
      }
    }

    else if ((h-> cycles > 1) && (h-> partial_cycle == 1))
    {
      static uint8_t count = 0;
      static uint8_t partial_set_flag = 0;
      static uint8_t partial_finished = 0;

      count++;

      if (count == (h-> cycles - 1))
      {
        partial_set_flag = 1;
      }

      else if (partial_set_flag == 1)
      {
        timer_reset_counter(h);
        set_partial_ocr_value(h);
        partial_set_flag = 0;
        partial_finished = 1;
      }

      else if ((partial_finished == 1))
      {
        timer_reset_counter(h);
        set_ocr_value(h);
        partial_finished = 0;
        count = 0;

        h-> callback();
      }
    }

  }
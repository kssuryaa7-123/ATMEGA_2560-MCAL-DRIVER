
#ifndef ATMEGA_2560_TIMER_REGDEF_H
#define ATMEGA_2560_TIMER_REGDEF_H


//=========================================
//REGISTER MAPPING FOR 8 BIT - TIMERS 0,2
//==========================================

//     *************REGISTER MAPPING FOR 8-BIT TIMER - 0********************
//REGISTER MAPPING FOR TIMER 0 (SYNCHRONOUS 8 BIT TIMER)...

//WHOLE TCCR0A register mapped detail...
#define TCCR0A (*(volatile uint8_t*)0X44) // address of TCCR0A
#define WGM00  0
#define WGM01  1
#define COM0B0 4
#define COM0B1 5
#define COM0A0 6
#define COM0A1 7

//WHOLE TCCROB register mapped detail
#define TCCR0B (*(volatile uint8_t*)0X45) // address of TCCR0B
#define CS00  0
#define CS01  1
#define CS02  2
#define WGM02 3
#define FOC0B 6
#define FOC0A 7 


#define TCNT0 (*(volatile uint8_t*)0X46) // address of timer0 counter register
#define OCR0A (*(volatile uint8_t*)0X47)//address of output compare registerA
#define OCR0B (*(volatile uint8_t*)0X48)//address of output compare registerB

//whole timer0 mask register mapping..
#define TIMSK0 (*(volatile uint8_t*)0X6E)//address of TIMER0 mask register
#define TOIE0  0
#define OCIE0A 1
#define OCIE0B 2

//whole register map of the timer0 flag register 
#define TIFR0 (*(volatile uint8_t*)0X35)//adress of timer0 flag register
#define TOV0  0
#define OCF0A 1
#define OCF0B 2

//-----------------------------------------------------------------------------------

//      *************REGISTER MAPPING FOR 8-BIT TIMER - 2********************
//REGISTER MAPPING FOR TIMER 2 (ASYNCHRONOUS 8 BIT TIMER)...

//WHOLE TCCR2A register mapped detail...
#define TCCR2A (*(volatile uint8_t*)0XB0) // address of TCCR2A
#define WGM20  0
#define WGM21  1
#define COM2B0 4
#define COM2B1 5
#define COM2A0 6
#define COM2A1 7

//WHOLE TCCR2B register mapped detail
#define TCCR2B (*(volatile uint8_t*)0XB1) // address of TCCR2B
#define CS20  0
#define CS21  1
#define CS22  2
#define WGM22 3
#define FOC2B 6
#define FOC2A 7 


#define TCNT2 (*(volatile uint8_t*)0XB2) // address of timer2 counter register
#define OCR2A (*(volatile uint8_t*)0XB3)//address of output compare registerA
#define OCR2B (*(volatile uint8_t*)0XB4)//address of output compare registerB

//TIMER 2 whole ASYNCHRONOUS REGISTER details..
#define ASSR (*(volatile uint8_t*)0XB6)
#define TCR2BUB 0
#define TCR2AUB 1
#define OCR2BUB 2
#define OCR2AUB 3
#define TCN2UB  4
#define AS2     5
#define EXCLK   6


//timer 2 whole mask register mapping..
#define TIMSK2 (*(volatile uint8_t*)0X70)//address of TIMER2 mask register
#define TOIE2  0
#define OCIE2A 1
#define OCIE2B 2

//whole register map of the timer2 flag register 
#define TIFR2 (*(volatile uint8_t*)0X37)//adress of timer0 flag register
#define TOV2  0
#define OCF2A 1
#define OCF2B 2


 //GTCCR – General Timer2/Counter2 Control Register
#define GTCCR (*(volatile uint8_t*)0X43)
#define PSRSYNC 0
#define PSRASY  1
#define TSM     7

//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------------

//================================================
//REGISTER MAPPING FOR 16 BIT - TIMERS 1,3,4,5
//================================================ 

//      **************REGISTER MAPPING FOR 16 BIT TIMER - 1***********************
//WHOLE TCCR1A regiater mapped details...
#define TCCR1A (*(volatile uint8_t*)0X80)//address of the TCCR1A
#define WGM10  0
#define WGM11  1
#define COM1C0 2
#define COM1C1 3
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7


//WHOLE TCCR1B register mapped details...
#define TCCR1B (*(volatile uint8_t*)0X81)//address of the TCCR1B
#define CS10  0
#define CS11  1
#define CS12  2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7


//WHOLE TCCR1C regiater mapped details...
#define TCCR1C (*(volatile uint8_t*)0X82)// ADDRESS OF THE TCCR1C
#define FOC1C 5
#define FOC1B 6
#define FOC1A 7

//WHOLE REGISTER MAPPING FOR THE TIMER FOR THE TCNT1H & TCNT1L
#define TCNT1H (*(volatile uint8_t*)0X85)// adress of upper count register timer1
#define TCNT1L (*(volatile uint8_t*)0x84)//address of lower count register timer1


//WHOLE REGISTER MAPPING FOR OCR REGIATER TIMER 1

//OUTPUT COMPARE REGISTER 1A
#define OCR1AH (*(volatile uint8_t*)0X89)// upper ocr register timer3
#define OCR1AL (*(volatile uint8_t*)0X88)// lower ocr register timer3
//OUTPUT COMPARE REGISTER 1B
#define OCR1BH (*(volatile uint8_t*)0X8B)// upper ocr register timer3
#define OCR1BL (*(volatile uint8_t*)0X8A)// lower ocr register timer3
//OUTPUT COMPARE REGISTER 1C
#define OCR1CH (*(volatile uint8_t*)0X8D)// upper ocr register timer3
#define OCR1CL (*(volatile uint8_t*)0X8C)// lower ocr register timer3



//whole register mapping detail for the input capture register
#define ICR1H (*(volatile uint8_t*)0X87)//UPPER INPUT CPTURE REGISTER VALUE 
#define ICR1L (*(volatile uint8_t*)0X86)//LOWER INPUT CAPTURE REGISTER VALUE 


//WHOLE REGISTER DETAILS of the timer1 mask register...
#define TIMSK1 (*(volatile uint8_t*)0x6F)//address of the mask register 
#define TOIE1  0
#define OCIE1A 1
#define OCIE1B 2
#define OCIE1C 3 
#define ICIE1  5


//whole register mapping  detail of the timer1 flag register 
#define TIFR1 (*(volatile uint8_t*)0x36)
#define TOV1  0
#define OCF1A 1
#define OCF1B 2
#define OCF1C 3
#define ICF1  5

//------------------------------------------------------------------------------------


//     **************REGISTER MAPPING FOR 16 BIT TIMER - 3***********************
//WHOLE TCCR3A regiater mapped details...
#define TCCR3A (*(volatile uint8_t*)0X90)//address of the TCCR3A
#define WGM30  0
#define WGM31  1
#define COM3C0 2
#define COM3C1 3
#define COM3B0 4
#define COM3B1 5
#define COM3A0 6
#define COM3A1 7


//WHOLE TCCR3B register mapped details...
#define TCCR3B (*(volatile uint8_t*)0X91)//address of the TCCR3B
#define CS30  0
#define CS31  1
#define CS32  2
#define WGM32 3
#define WGM33 4
#define ICES3 6
#define ICNC3 7


//WHOLE TCCR3C regiater mapped details...
#define TCCR3C (*(volatile uint8_t*)0X92)// ADDRESS OF THE TCCR3C
#define FOC3C 5
#define FOC3B 6
#define FOC3A 7

//WHOLE REGISTER MAPPING FOR THE TIMER FOR THE TCNT3H & TCNT3L
#define TCNT3H (*(volatile uint8_t*)0X95)// adress of upper count register timer3
#define TCNT3L (*(volatile uint8_t*)0x94)//address of lower count register timer3


//WHOLE REGISTER MAPPING FOR OCR REGISTER TIMER 3

//OUTPUT COMPARE REGISTER 3A
#define OCR3AH (*(volatile uint8_t*)0X99)// upper ocr register timer3
#define OCR3AL (*(volatile uint8_t*)0X98)// lower ocr register timer3
//OUTPUT COMPARE REGISTER 3B
#define OCR3BH (*(volatile uint8_t*)0X9B)// upper ocr register timer3
#define OCR3BL (*(volatile uint8_t*)0X9A)// lower ocr register timer3
//OUTPUT COMPARE REGISTER 3C
#define OCR3CH (*(volatile uint8_t*)0X9D)// upper ocr register timer3
#define OCR3CL (*(volatile uint8_t*)0X9C)// lower ocr register timer3


//whole register mapping detail for the input capture register
#define ICR3H (*(volatile uint8_t*)0X97)//UPPER INPUT CPTURE REGISTER VALUE 
#define ICR3L (*(volatile uint8_t*)0X96)//LOWER INPUT CAPTURE REGISTER VALUE 


//WHOLE REGISTER DETAILS of the timer3 mask register...
#define TIMSK3 (*(volatile uint8_t*)0x71)//address of the mask register 
#define TOIE3  0
#define OCIE3A 1
#define OCIE3B 2
#define OCIE3C 3 
#define ICIE3  5


//whole register mapping  detail of the timer3 flag register 
#define TIFR3 (*(volatile uint8_t*)0x38)
#define TOV3  0
#define OCF3A 1
#define OCF3B 2
#define OCF3C 3
#define ICF3  5

//-----------------------------------------------------------------------------------
//**************REGISTER MAPPING FOR 16 BIT TIMER - 4***********************
//WHOLE TCCR4A regiater mapped details...
#define TCCR4A (*(volatile uint8_t*)0XA0)//address of the TCCR4A
#define WGM40  0
#define WGM41  1
#define COM4C0 2
#define COM4C1 3
#define COM4B0 4
#define COM4B1 5
#define COM4A0 6
#define COM4A1 7


//WHOLE TCCR4B register mapped details...
#define TCCR4B (*(volatile uint8_t*)0XA1)//address of the TCCR4B
#define CS40  0
#define CS41  1
#define CS42  2
#define WGM42 3
#define WGM43 4
#define ICES4 6
#define ICNC4 7


//WHOLE TCCR4C regiater mapped details...
#define TCCR4C (*(volatile uint8_t*)0XA2)// ADDRESS OF THE TCCR4C
#define FOC4C 5
#define FOC4B 6
#define FOC4A 7

//WHOLE REGISTER MAPPING FOR THE TIMER FOR THE TCNT4H & TCNT4L
#define TCNT4H (*(volatile uint8_t*)0XA5)// adress of upper count register timer4
#define TCNT4L (*(volatile uint8_t*)0xA4)//address of lower count register timer4


//WHOLE REGISTER MAPPING FOR OCR REGISTER TIMER 4

//OUTPUT COMPARE REGISTER 4A
#define OCR4AH (*(volatile uint8_t*)0XA9)// upper ocr register timer4
#define OCR4AL (*(volatile uint8_t*)0XA8)// lower ocr register timer4
//OUTPUT COMPARE REGISTER 4B
#define OCR4BH (*(volatile uint8_t*)0XAA)// upper ocr register timer4
#define OCR4BL (*(volatile uint8_t*)0XAB)// lower ocr register timer4
//OUTPUT COMPARE REGISTER 4C
#define OCR4CH (*(volatile uint8_t*)0XAD)// upper ocr register timer4
#define OCR4CL (*(volatile uint8_t*)0XAC)// lower ocr register timer4


//whole register mapping detail for the input capture register
#define ICR4H (*(volatile uint8_t*)0XA7)//UPPER INPUT CPTURE REGISTER VALUE 
#define ICR4L (*(volatile uint8_t*)0XA6)//LOWER INPUT CAPTURE REGISTER VALUE 


//WHOLE REGISTER DETAILS of the timer4 mask register...
#define TIMSK4 (*(volatile uint8_t*)0x72)//address of the mask register 
#define TOIE4  0
#define OCIE4A 1
#define OCIE4B 2
#define OCIE4C 3 
#define ICIE4  5


//whole register mapping  detail of the timer4 flag register 
#define TIFR4 (*(volatile uint8_t*)0x39)
#define TOV4  0
#define OCF4A 1
#define OCF4B 2
#define OCF4C 3
#define ICF4  5

//-----------------------------------------------------------------------------------
//**************REGISTER MAPPING FOR 16 BIT TIMER - 5***********************
//WHOLE TCCR5A regiater mapped details...
#define TCCR5A (*(volatile uint8_t*)0X120)//address of the TCCR5A
#define WGM50  0
#define WGM51  1
#define COM5C0 2
#define COM5C1 3
#define COM5B0 4
#define COM5B1 5
#define COM5A0 6
#define COM5A1 7


//WHOLE TCCR5B register mapped details...
#define TCCR5B (*(volatile uint8_t*)0X121)//address of the TCCR5B
#define CS50  0
#define CS51  1
#define CS52  2
#define WGM52 3
#define WGM53 4
#define ICES5 6
#define ICNC5 7


//WHOLE TCCR5C regiater mapped details...
#define TCCR5C (*(volatile uint8_t*)0X122)// ADDRESS OF THE TCCR5C
#define FOC5C 5
#define FOC5B 6
#define FOC5A 7

//WHOLE REGISTER MAPPING FOR THE TIMER FOR THE TCNT5H & TCNT5L
#define TCNT5H (*(volatile uint8_t*)0X125)// adress of upper count register timer5
#define TCNT5L (*(volatile uint8_t*)0x124)//address of lower count register timer5


//WHOLE REGISTER MAPPING FOR OCR REGISTER TIMER 5

//OUTPUT COMPARE REGISTER 5A
#define OCR5AH (*(volatile uint8_t*)0X129)// upper ocr register timer5
#define OCR5AL (*(volatile uint8_t*)0X128)// lower ocr register timer5
//OUTPUT COMPARE REGISTER 5B
#define OCR5BH (*(volatile uint8_t*)0X12B)// upper ocr register timer5
#define OCR5BL (*(volatile uint8_t*)0X12A)// lower ocr register timer5
//OUTPUT COMPARE REGISTER 5C
#define OCR5CH (*(volatile uint8_t*)0X12D)// upper ocr register timer5
#define OCR5CL (*(volatile uint8_t*)0X12C)// lower ocr register timer5


//whole register mapping detail for the input capture register
#define ICR5H (*(volatile uint8_t*)0X127)//UPPER INPUT CPTURE REGISTER VALUE 
#define ICR5L (*(volatile uint8_t*)0X126)//LOWER INPUT CAPTURE REGISTER VALUE 


//WHOLE REGISTER DETAILS of the timer5 mask register...
#define TIMSK5 (*(volatile uint8_t*)0x73)//address of the mask register 
#define TOIE5  0
#define OCIE5A 1
#define OCIE5B 2
#define OCIE5C 3 
#define ICIE5  5


//whole register mapping  detail of the timer5 flag register 
#define TIFR5 (*(volatile uint8_t*)0x3A)
#define TOV5  0
#define OCF5A 1
#define OCF5B 2
#define OCF5C 3
#define ICF5  5

//------------------------------------------------------------------------------------

#endif
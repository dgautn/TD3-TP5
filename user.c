/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif

#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */
    TRISBbits.TRISB2 = 0;   /* led1 */
    TRISBbits.TRISB3 = 0;   /* led2 */
    TRISBbits.TRISB7 = 1;   /* boton1 */
    /* Initialize peripherals */
}


void ConfigTimer(void)
{
    T3CONbits.TON = 0;         // Stop any 16-bit Timer3 operation		
    T2CONbits.TON = 0;        // Stop any 16/32-bit Timer2 operation
    T2CONbits.T32 = 1;        // Enable 32-bit Timer mode
    T2CONbits.TCS = 0;        // Select internal instruction cycle clock
    T2CONbits.TGATE = 0;      // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b00;   // Select 1:1 Prescaler
    TMR3 = 0x00;              // Clear 32-bit Timer (msw)
    TMR2 = 0x00;              // Clear 32-bit Timer (lsw)
    PR3 = 0x0002;             // Load 32-bit period value (msw)
    PR2 = 0x0000;             // Load 32-bit period value (lsw)

    IPC2bits.T3IP = 0x01;     // Set Timer3 Interrupt Priority Level
    IFS0bits.T3IF = 0;        // Clear Timer3 Interrupt Flag
    IEC0bits.T3IE = 1;        // Enable Timer3 interrupt

    T2CONbits.TON = 1;        // Start 32-bit Timer
}
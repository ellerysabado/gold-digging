/*
*
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9

#include "Timer.h"
#include "lcd.h"
#include "movement.h"
#include "open_interface.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "button.h"
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "uart-interrupt.h"
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include "uart.h"
#include "adc.h"

#include "Timer.h"
#include "lcd.h"
#include "ping_template.h"

// Uncomment or add any include directives that are needed

//#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

	// YOUR CODE HERE

	// o initialize PB3 as a digital output
	//This is done by writing 0-1-0 to the GPIODATA register bit.






	// this is the key?
//	GPIO Port B pin 3 (PB3)
//	Timer3B Capture/Compare/PWM (CCP) pin
//	Connects to the input/output pin of the Ping))) sensor


	// how long should the trigger pulse be high? answer: 5 Mili?
	int j;

	while(1)
	{
	    timer_waitMillis(500);
	    lcd_clear();

	    double ping = ping_getDistance();


//	    printf("Ping: \r%f\n", ping);
        char str1[10];
        sprintf(str1, "Ping: %f", ping);
        for(j = 0; j < strlen(str1); j++){
            lcd_putc(str1[j]);
        }

        lcd_gotoLine(2);
        int pulseLength = getPulseLength();
        char str3[10];
        sprintf(str3, "Pulse Length: %d", pulseLength);
        for (j = 0; j < strlen(str3); j++){
            lcd_putc(str3[j]);
        }

        lcd_gotoLine(3);
        int overflow = getOverflow();
        char str2[10];
        sprintf(str2, "Overflow: %d", overflow);
        for (j = 0; j < strlen(str2); j++){
            lcd_putc(str2[j]);
        }


	}


}
*/

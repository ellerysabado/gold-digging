/*
*
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016


#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1
#include <string.h>
//#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
    cyBot_uart_init();
	            // Don't forget to initialize the cyBot UART before trying to use it

	// YOUR CODE HERE
    int j;

	
	while(1)
	{

	    int button = button_getButton();
	    lcd_printf("%d", button);

        if (button == 4)
        {
            char str[30] = "\r\nThe right most button is pressed";
            for (j = 0; j < strlen(str); j++)
            {
                cyBot_sendByte(str[j]);
            }

        }
        else if (button == 3)
        {
            char str[30] = "\r\nThe second right most button is pressed";
            for (j = 0; j < strlen(str); j++)
            {
                cyBot_sendByte(str[j]);
            }
        }
        else if (button == 2)
        {
            char str[30] = "\r\nThe second left most button is pressed";
            for (j = 0; j < strlen(str); j++)
            {
                cyBot_sendByte(str[j]);
            }
        }
        else if (button == 1)
        {
            char str[30] = "\r\nThe lest most button is pressed";
            for (j = 0; j < strlen(str); j++)
            {
                cyBot_sendByte(str[j]);
            }
        }



	}

}
*/

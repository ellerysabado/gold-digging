/*
 * scanning.c This is c file that uses the servo moder to scan the object and get its data
 *
 *  Created on: Apr 24, 2023
 *      Author: elsabado
 */

#include "lcd.h"
#include "timer.h"
#include "button.h"
#include "servo.h"
#include "ping_template.h"
#include "uart.h"
#include "movement.h"
#include "open_interface.h"
#include "scanning.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inc/tm4c123gh6pm.h>

double objects[16][5];

int i = 0, j = 0, k = 0, l = 0;
double degreesPING[181]; // This is the array for each degree
int IR[181]; //This is for IR data
double degreesPING1[91]; // This is the array for each degree
int IR1[91]; //This is for IR data
int count = 0;
char str[30];
char dist[10];

//    int numobject = 0, initAngle = 0; finalAngle = 0, dist = 0, radius = 0;

void freeScan(void)
{
    for (i = 0; i < 16; i++)
    { // Clear the objects inside
        for (j = 0; j < 5; j++)
        {
            objects[i][j] = 0;
        }
    }

    for (i = 0; i <= 180; i++)
    { // Clears the degrees data
        degreesPING[i] = 0;
        IR[i] = 0;
    }
}

void freeScan1(void)
{
    for (i = 0; i < 16; i++)
    { // Clear the objects inside
        for (j = 0; j < 5; j++)
        {
            objects[i][j] = 0;
        }
    }

    for (i = 0; i <= 90; i++)
    { // Clears the degrees data
        degreesPING1[i] = 0;
        IR1[i] = 0;
    }
}

/**
 * This function does the 180 degree scan and detect objects around
 *
 * The input is the 16 objects and the 5 key features of an object
 *
 * This is the main stuff from lab 7 from main function into its own scanning
 */
void scanShortAll(void)
{ // 1 = distance, 2 = initial angle, 3 = final angle, 4 = radius
    servo_move(0);
    freeScan1();


    sprintf(str, "\r\nAngle\tDistance\r\n");
    uart_sendStr(str);
//    printf(str);

    timer_waitMillis(700); // This is for waiting for the server to move back to orginal position
    l=0;
    for (i = 0; i <= 180; i += 2)
    { // getting data, averaging it out and stroin it in array to dertermine objects
        servo_move(i);

        double distance = ping_getDistance();
        timer_waitMillis(5);
        distance += ping_getDistance();
        timer_waitMillis(5);
        distance += ping_getDistance();
        timer_waitMillis(5);
        distance += ping_getDistance();

        distance = distance / 4;
        degreesPING1[l] = distance;
        IR1[l] = adc_read();
        sprintf(str, "\r\n%d\t%f\t%d", i, distance, adc_read());
        uart_sendStr(str);
//        printf(str);
        l++;
    }
    uart_sendChar('\r');
    uart_sendChar('\n');
    k = -2;
    for (i = 0; i <= 90; i++)
    {
        k += 2;

        sprintf(str, "%d", k);
        sprintf(dist, "%d", (int) degreesPING1[i]);
        uart_sendStr(str);
        count = (int) IR1[i];
        count /= 20;
        for (j = 0; j < count; j++)
        {
            uart_sendChar('-');
        }
        uart_sendStr(dist);
        uart_sendChar('\r');
        uart_sendChar('\n');

    }
}

void scanAll(/*double objects[16][5]*/void)
{ // 1 = distance, 2 = initial angle, 3 = final angle, 4 = radius
    servo_move(0);
    freeScan();


    sprintf(str, "\r\nAngle\tDistance\r\n");
    uart_sendStr(str);
//    printf(str);

    timer_waitMillis(700); // This is for waiting for the server to move back to orginal position
    for (i = 0; i <= 180; i++)
    { // getting data, averaging it out and stroin it in array to dertermine objects
        servo_move(i);

        double distance = ping_getDistance();
        timer_waitMillis(5);
        distance += ping_getDistance();
        timer_waitMillis(5);
        distance += ping_getDistance();
        timer_waitMillis(5);
        distance += ping_getDistance();

        distance = distance / 4;
        degreesPING[i] = distance;
        IR[i] = adc_read();
        sprintf(str, "\r\n%d\t%f\t%d", i, distance, adc_read());
        uart_sendStr(str);
//        printf(str);
    }

    for (i = 0; i <= 180; i++)
    {

        sprintf(str, "%d", i);
        sprintf(dist, "%d", (int) degreesPING[i]);
        uart_sendStr(dist);
        count = (int) IR[i];
        count /= 20;
        uart_sendChar('\r');
        uart_sendChar('\n');
        uart_sendStr(str);
        for (j = 0; j < count; j++)
        {
            uart_sendChar('-');
        }

    }
}

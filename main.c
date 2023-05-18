/**
 * This is the main function of the code to find the gold in the field.
 *
 * @author Ellery Sabado, William Griner, Matthew Nevin, Regassa Dukele
 * @date 4/18/2023
 *
 */

#include "lcd.h"
#include "Timer.h"
#include "movement.h"
#include "open_interface.h"
#include "button.h"
#include "uart.h"
#include "adc.h"
#include "ping_template.h"
#include "servo.h"
#include "music.h"
#include "driverlib/interrupt.h"
#include "scanning.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inc/tm4c123gh6pm.h>

void music_init(void);

void main()
{
    char byte;
    int data = 0;
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
//    oi_free(sensor_data);
//    oi_setWheels(100, 100);
    timer_init();
    lcd_init();
    uart_init();
    adc_init();
    ping_init();
    servo_init();
    music_init();
//    freeScan();
//    oi_play_song(RICK_ROLL);

//    load_songs();
//    oi_play_song(IMERPIAL_MARCH); // RICK_ROLL and IMPERIAL_MARCH both work.

    char message[30];
//    oi_free(sensor_data);
//    oi_setWheels(0, 0);
    while (1)
    {
        oi_update(sensor_data);
        byte = uart_receive();
//        uart_sendChar(byte);

        /**
         * starts the program when m is pressed or bummped
         */
        if (byte == 'm')
        {
            scanAll(/*obj*/);
        }
        else if (byte == 'n')
        {
            scanShortAll();
        }
        else if (byte == 'w')
        {
            move_forward(sensor_data, 5);
            sprintf(message, "\r\n5mm forward");
                        uart_sendStr(message);
        }
        else if (byte == 's')
        {
            move_back(sensor_data, 5);
            sprintf(message, "\r\n5mm backward");
            uart_sendStr(message);
        }
        else if (byte == 'a')
        {
            turn_left(sensor_data, 5);
            sprintf(message, "\r\n5mm turned left");
            uart_sendStr(message);
        }
        else if (byte == 'd')
        {
            turn_right(sensor_data, 5);
            sprintf(message, "\r\n5mm turned right");
            uart_sendStr(message);
        }
        else if (byte == '4')
        {
            turn_left(sensor_data, 85);
            sprintf(message, "\r\n90 degree turn left");
            uart_sendStr(message);
        }
        else if (byte == '6')
        {
            turn_right(sensor_data, 85);
            sprintf(message, "\r\n90 degree turn right");
            uart_sendStr(message);
        }
        else if (byte == '1')
        {
            turn_left(sensor_data, 14);
            sprintf(message, "\r\n15 degree turn left");
            uart_sendStr(message);
        }
        else if (byte == '3')
        {
            turn_right(sensor_data, 14);
            sprintf(message, "\r\n15 degree turn right");
            uart_sendStr(message);
        }
        else if (byte == '8')
        {
            move_forward(sensor_data, 100);
            sprintf(message, "\r\n10 cm moved forward");
            uart_sendStr(message);
        }
        else if (byte == '2')
        {
            move_back(sensor_data, 100);
            sprintf(message, "\r\n10 cm moved backward");
            uart_sendStr(message);
        }
        else if (byte == '`')
        {
            sprintf(message, "\r\nDONE");
            uart_sendStr(message);
            oi_play_song(RICK_ROLL);
//            turn_right(sensor_data, 90);
//            turn_right(sensor_data, 90);
//            turn_right(sensor_data, 90);
//            turn_right(sensor_data, 90);
            oi_free(sensor_data);
            break;
        }
        else if (byte == 'z') //left
        {

            data = sensor_data->cliffLeftSignal;
            sprintf(message, "\r\n%d left cliff signal", data);
            uart_sendStr(message);

            oi_update(sensor_data);
        }
        else if (byte == 'x') // front left
        {

            data = sensor_data->cliffFrontLeftSignal;
            sprintf(message, "\r\n%d front Left Cliff Signal", data);
            uart_sendStr(message);

            oi_update(sensor_data);
        }
        else if (byte == 'c') // front right
        {

            data = sensor_data->cliffFrontRightSignal;
            sprintf(message, "\r\n%d front Right Cliff Signal", data);
            uart_sendStr(message);

            oi_update(sensor_data);
        }
        else if (byte == 'v') // right
        {

            data = sensor_data->cliffRightSignal;
            sprintf(message, "\r\n%d Right Cliff Signal", data);
            uart_sendStr(message);

            oi_update(sensor_data);
        }

        /**
         * GOLD
         */
        if (sensor_data->cliffLeftSignal <= 2880
                && sensor_data->cliffLeftSignal >= 2830)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nGOLD - Cliff Left");
            uart_sendStr(message);
            oi_play_song(MARIO_UNDERWORLD);

        }
        else if (sensor_data->cliffFrontLeftSignal <= 2880
                && sensor_data->cliffFrontLeftSignal >= 2830)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nGOLD - Cliff Front Left");
            uart_sendStr(message);
            oi_play_song(MARIO_UNDERWORLD);

        }
        else if (sensor_data->cliffFrontRightSignal <= 2880
                && sensor_data->cliffFrontRightSignal >= 2820)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nGOLD - Cliff Front Right");
            uart_sendStr(message);
            oi_play_song(MARIO_UNDERWORLD);

        }
        else if (sensor_data->cliffRightSignal <= 2880
                && sensor_data->cliffRightSignal >= 2830)  // max:2770  min:2753
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nGOLD - Cliff Right");
            uart_sendStr(message);
            oi_play_song(MARIO_UNDERWORLD);

        }

        /**
         * WHITE (Bound)
         */
        if (sensor_data->cliffLeftSignal <= 2770
                && sensor_data->cliffLeftSignal >= 2720)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nOUT OF BOUNDS - Cliff Left");
            uart_sendStr(message);
            move_back(sensor_data, 50);

            timer_waitMillis(2000);

        }
        else if (sensor_data->cliffFrontLeftSignal <= 2770
                && sensor_data->cliffFrontLeftSignal >= 2720)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nOUT OF BOUNDS - Cliff Front Left");
            uart_sendStr(message);
            move_back(sensor_data, 50);

            timer_waitMillis(2000);

        }
        else if (sensor_data->cliffFrontRightSignal <= 2770
                && sensor_data->cliffFrontRightSignal >= 2720)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nOUT OF BOUNDS - Cliff Front Right");
            uart_sendStr(message);
            move_back(sensor_data, 50);

            timer_waitMillis(2000);

        }
        else if (sensor_data->cliffRightSignal <= 2630
                && sensor_data->cliffRightSignal >= 2580)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nOUT OF BOUNDS - Cliff Right");
            uart_sendStr(message);
            move_back(sensor_data, 50);

            timer_waitMillis(2000);
        }

        /**
         * This is the check for cliff sensor
         */
        if (sensor_data->cliffLeft)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nCliff Left DANGER CLIFF");
            uart_sendStr(message);

            move_back(sensor_data, 100);

            oi_play_song(2);
            timer_waitMillis(2000);

        }
        else if (sensor_data->cliffFrontLeft)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nCliff Front Left DANGER CLIFF");
            uart_sendStr(message);

            move_back(sensor_data, 100);
            oi_play_song(2);
            timer_waitMillis(2000);

        }
        else if (sensor_data->cliffFrontRight)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nCliff Front Right DANGER CLIFF");
            uart_sendStr(message);

            move_back(sensor_data, 100);
            oi_play_song(2);
            timer_waitMillis(2000);

        }
        else if (sensor_data->cliffRight)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nCliff Right DANGER CLIFF");
            uart_sendStr(message);

            move_back(sensor_data, 100);
            oi_play_song(2);
            timer_waitMillis(2000);

        }

        if (sensor_data->bumpLeft)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nBumped Left");
            uart_sendStr(message);

            move_back(sensor_data, 30);
            oi_play_song(IMERPIAL_MARCH);

            timer_waitMillis(2000);

        }
        else if (sensor_data->bumpRight)
        {
            oi_update(sensor_data);
            sprintf(message, "\r\nBumped Right");
            uart_sendStr(message);

            move_back(sensor_data, 30);
            oi_play_song(IMERPIAL_MARCH);

            timer_waitMillis(2000);

        }

    }

}

void music_init()
{
    unsigned char backupNotes[2] = { 84, 0 };
    unsigned char backupDuration[4] = { 32, 32 };
    oi_loadSong(2, 2, backupNotes, backupDuration);

    unsigned char succNotes[7] = { 57, 0, 58, 0, 59, 0, 60 };
    unsigned char succDuration[7] = { 20, 4, 24, 4, 24, 4, 48 };
    oi_loadSong(1, 7, succNotes, succDuration);

    unsigned char rickrollNumNotes = 11;
    unsigned char rickrollNotes[11] = { 53, 55, 48, 55, 57, 60, 58, 57, 53, 55,
                                        48 };
    unsigned char rickrollDuration[11] = { 48, 64, 16, 48, 48, 8, 8, 8, 48, 64,
                                           64 };
    oi_loadSong(RICK_ROLL, rickrollNumNotes, rickrollNotes, rickrollDuration);
//    unsigned char ImperialMarchNumNotes = 19;
//    unsigned char ImperialMarchNotes[19] = { 55, 55, 55, 51, 58, 55, 51, 58, 55,
//                                             0, 62, 62, 62, 63, 58, 54, 51, 58,
//                                             55 };
//    unsigned char ImperialMarchDurations[19] = { 32, 32, 32, 20, 12, 32, 20, 12,
//                                                 32, 32, 32, 32, 32, 20, 12, 32,
//                                                 20, 12, 32 };
//    oi_loadSong(IMERPIAL_MARCH, ImperialMarchNumNotes, ImperialMarchNotes,
//                ImperialMarchDurations);
//
//    unsigned char mario1NumNotes = 49;
//    unsigned char mario1Notes[49]    = {48, 60, 45, 57, 46, 58,  0, 48, 60, 45, 57, 46, 58,  0, 41, 53, 38, 50, 39, 51,  0, 41, 53, 38, 50, 39, 51,  0, 51, 50, 49, 48, 51, 50, 44, 43, 49, 48, 54, 53, 52, 58, 57, 56, 51, 47, 46, 45, 44 };
//    unsigned char mario1Duration[49] = {12, 12, 12, 12, 12, 12, 62, 12, 12, 12, 12, 12, 12, 62, 12, 12, 12, 12, 12, 12, 62, 12, 12, 12, 12, 12, 12, 48,  8,  8,  8, 24, 24, 24, 24, 24, 24,  8,  8,  8,  8,  8,  8, 16, 16, 16, 16, 16, 16 };
//    oi_loadSong(MARIO_UNDERWORLD, mario1NumNotes, mario1Notes, mario1Duration);
}

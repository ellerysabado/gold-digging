/*
 * movement.c
 *
 *  Created on: Jan 31, 2023
 *      Author: elsabado
 */
#include "movement.h"

double move_forward(oi_t *sensor_data, double distance_mm){

    double sum = 0;
    oi_setWheels(100, 100);
    while (sum < distance_mm)
    {
        oi_update(sensor_data);
        sum += sensor_data->distance;

    }
    oi_setWheels(0, 0);

    return 0;
}

double move_back(oi_t *sensor_data, double distance_mm){

    double sum = 0;
    oi_setWheels(-100, -100);
    while (sum > (-1* distance_mm))
    {
        oi_update(sensor_data);
        sum += sensor_data->distance;

    }
    oi_setWheels(0, 0);

    return 0;
}

double turn_right(oi_t *sensor_data, double degree){
    double angle = 0;
    oi_setWheels(-100, 100);
    while ((-1 * degree) < angle){
        oi_update(sensor_data);
        angle += sensor_data->angle;

    }
    oi_setWheels(0, 0);

    return 0;
}


double turn_left(oi_t *sensor_data, double degree)
{
    double angle = 0;
    oi_setWheels(100, -100);
    while (degree > angle)
    {
        oi_update(sensor_data);
        angle += sensor_data->angle;

    }
    oi_setWheels(0, 0);
    return 0;
}


/*
 * movement.h
 *
 *  Created on: Jan 31, 2023
 *      Author: elsabado
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
#include "open_interface.h"


double move_forward(oi_t *sensor_data, double distance_mm);
double move_back(oi_t *sensor_data, double distance_mm);
double turn_right(oi_t *sensor_data, double degree);
double turn_left(oi_t *sensor_data, double degree);


#endif /* MOVEMENT_H_ */

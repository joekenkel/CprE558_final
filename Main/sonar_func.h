#ifndef SONAR_FUNC_H
#define SONAR_FUNC_H
#include "types.h"
#include "Arduino.h"
#include <stdio.h>

// User functions
void run_ping(short trig_pin, short echo_pin, sonar_task* my_task);

// State functions
void ping_state(short trig_pin, short echo_pin, long* duration);
void compute_distance(long* duration,int* distance);

// helper functions
void trigger_sonar(short trig_pin);


#endif

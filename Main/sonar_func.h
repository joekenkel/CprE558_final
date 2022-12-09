#ifndef SONAR_FUNC_H
#define SONAR_FUNC_H
#include "types.h"
#include "Arduino.h"
#include <stdio.h>

// User functions
void run_cnt(task* my_task);
void run_ping(short trig_pin, short echo_pin, sonar_task* my_task);

void ping_state(short trig_pin, short echo_pin, long* duration);

// helper functions
void trigger_sonar(short trig_pin);
void compute_distance(long* duration,int* distance);

#endif

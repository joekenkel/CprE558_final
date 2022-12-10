#ifndef CONTROL_FUNC_H
#define CONTROL_FUNC_H
#include "types.h"
#include "Arduino.h"

// User functions
void run_cnt(task* my_task,direction_info* dir_info,
              int sonar0,int sonar1,int sonar2);

// State function            
void process_response(task* my_task,direction_info* dir_info,
              int sonar0,int sonar1,int sonar2);
void update_wheels(task* my_task,direction_info* dir_info);

// Helper functions
void stop_wheels();
void go_forward();
void turn_left();
void turn_right();

#endif CONTROL_FUNC_H

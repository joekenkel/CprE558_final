#ifndef TASK_H
#define TASK_H
#include "Arduino.h"
#include "types.h"

// int structs
void int_control(task* rst_task);
void int_sonar0(sonar_task* rst_task);
void int_sonar1(sonar_task* rst_task);
void int_sonar2(sonar_task* rst_task);
void int_direction(direction_info* rst_task);

// update structs
void update_task(task* update_task,long idx,int period, short , short miss_allowed);
void reset_task(task* rst_task, int priod);
void update_miss_history(task* update_task, short k, byte hit);
void int_direction(direction_info* int_task);

// user functions
void sel_task(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             direction_info* dir_info);

void update_tasks(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             long task_idx);

void print_sonar(sonar_task t_sonar);
void print_task(task t_control);
#endif

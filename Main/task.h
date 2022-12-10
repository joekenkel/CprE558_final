#ifndef TASK_H
#define TASK_H
#include "Arduino.h"
#include "types.h"
#include "sonar_func.h"

void int_control(task* rst_task);
void int_sonar0(sonar_task* rst_task);
void int_sonar1(sonar_task* rst_task);
void int_sonar2(sonar_task* rst_task);
void int_direction(direction_info* rst_task);

void reset_task(task* rst_task, int priod);
void int_direction(direction_info* int_task);

void sel_task(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             direction_info* dir_info);

void calculate_manditory(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             int task_idx);

void update_tasks(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             int task_idx);

#endif

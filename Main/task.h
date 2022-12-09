#ifndef TASK_H
#define TASK_H
#include "Arduino.h"
#include "types.h"
#include "sonar_func.h"

void reset_control(task* rst_task);
void reset_sonar0(sonar_task* rst_task);
void reset_sonar1(sonar_task* rst_task);
void reset_sonar2(sonar_task* rst_task);

void sel_task(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             int task_idx);

void calculate_manditory(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             int task_idx);

#endif

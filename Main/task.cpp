#include "task.h"


void reset_control(task* rst_task){
  rst_task->current_state = 1;
  rst_task->compute = control_compute;
  rst_task->deadline += control_period;
  rst_task->laxity = control_period - control_compute;
}
void reset_sonar0(sonar_task* rst_task){
  rst_task->task_info.current_state = 1;
  rst_task->task_info.compute = sonar0_compute;
  rst_task->task_info.deadline += sonar0_period;
  rst_task->task_info.laxity = sonar0_period - sonar0_compute;
}

void reset_sonar1(sonar_task* rst_task){
  rst_task->task_info.current_state = 1;
  rst_task->task_info.compute = sonar0_compute;
  rst_task->task_info.deadline += sonar0_period;
  rst_task->task_info.laxity = sonar0_period - sonar0_compute;
}

void reset_sonar2(sonar_task* rst_task){
  rst_task->task_info.current_state = 1;
  rst_task->task_info.compute = sonar0_compute;
  rst_task->task_info.deadline += sonar0_period;
  rst_task->task_info.laxity = sonar0_period - sonar0_compute;
}

void reset_direction(direction_info* rst_task){
  rst_task->x = 0;
  rst_task->y = 0;
  rst_task->angle = 0;
  rst_task->turn_left = false;
  rst_task->turn_right = false;
}

void sel_task(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             direction_info* dir_info, int task_idx){
              
  // make it easier to type
  int cnt_num = t_control->deadline;
  int sonar0_num = t_sonar0->task_info.deadline;
  int sonar1_num = t_sonar1->task_info.deadline;
  int sonar2_num = t_sonar2->task_info.deadline;

  // on a tie t_cnt -> sonar0 -> sonar1 -> sonar2
  if (cnt_num <= sonar0_num && cnt_num <= sonar1_num && 
      cnt_num <= sonar2_num && 
      t_control->current_state < control_compute){ 
        //Control has the closest deadline
    Serial.println("control is running");
    run_cnt(t_control,dir_info,
              t_sonar0->distance,t_sonar1->distance,t_sonar2->distance);
              
  }else if(sonar0_num <= sonar1_num && sonar0_num <= sonar1_num &&
            t_sonar0->task_info.current_state < sonar0_compute){ 
              // sonar0 has the closest deadline
    Serial.println("Sonar0 is running");
    run_ping(sonar0_trig, sonar0_echo, t_sonar0);
  }else if(sonar1_num <= sonar2_num && t_sonar1->task_info.current_state < sonar1_compute){ // sonar1 has the closest deadline
    Serial.println("Sonar1 is running");
    run_ping(sonar1_trig, sonar1_echo, t_sonar1);
  }else if(t_sonar2->task_info.current_state < sonar2_compute){// sonar2 has the closest deadline
    Serial.println("Sonar2 is running");
    run_ping(sonar2_trig, sonar2_echo, t_sonar2);
  }else {
    Serial.println("No task is running");
  }

}

void calculate_manditory(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             int task_idx){

  //TODO FIGURE OUT THIS
  
              
}

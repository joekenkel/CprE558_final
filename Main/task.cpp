#include "task.h"

void int_control(task* int_task){
  int_task->taskId = 69;
  int_task->current_state = 1;
  int_task->compute = control_compute;
  int_task->deadline += control_period;
  int_task->laxity = control_period - control_compute;
}
void int_sonar0(sonar_task* int_task){
  int_task->task_info.taskId = 0;
  int_task->task_info.current_state = 1;
  int_task->task_info.compute = sonar0_compute;
  int_task->task_info.deadline += sonar0_period;
  int_task->task_info.laxity = sonar0_period - sonar0_compute;
}

void int_sonar1(sonar_task* int_task){
  int_task->task_info.taskId = 1;
  int_task->task_info.current_state = 1;
  int_task->task_info.compute = sonar0_compute;
  int_task->task_info.deadline += sonar0_period;
  int_task->task_info.laxity = sonar0_period - sonar0_compute;
}

void int_sonar2(sonar_task* int_task){
  int_task->task_info.taskId = 2;
  int_task->task_info.current_state = 1;
  int_task->task_info.compute = sonar0_compute;
  int_task->task_info.deadline += sonar0_period;
  int_task->task_info.laxity = sonar0_period - sonar0_compute;
}

void int_direction(direction_info* int_task){
  int_task->x = 0;
  int_task->y = 0;
  int_task->angle = 0;
  int_task->turn_left = false;
  int_task->turn_right = false;
}

void update_task(task* update_task,int idx,int period){
  if(idx == update_task->deadline){
#if debug
  char temp_str[35];
  sprintf(temp_str, "Tast %d reset at index %d\n", update_task->taskId,idx);
  Serial.print(temp_str);
#endif
    reset_task(update_task, period);
  }else{
    update_task->laxity -= 1;
  }
}

void reset_task(task* rst_task, int period){
  rst_task->current_state = 1;
  rst_task->deadline += period;
  rst_task->laxity = period - rst_task->compute;
}

void sel_task(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             direction_info* dir_info){
              
  // make it easier to type
  bool cnt_check = t_control->laxity >= 0 && t_control->current_state <= control_compute;
  int cnt_num = cnt_check ? t_control->deadline : int_max;
  bool sonar0_check = t_sonar0->task_info.laxity >= 0 && t_sonar0->task_info.current_state <= sonar0_compute;
  int sonar0_num = sonar0_check ? t_sonar0->task_info.deadline : int_max;
  bool sonar1_check = t_sonar1->task_info.laxity >= 0 && t_sonar1->task_info.current_state <= sonar1_compute;
  int sonar1_num = sonar1_check ? t_sonar1->task_info.deadline : int_max;
  bool sonar2_check = t_sonar2->task_info.laxity >= 0 && t_sonar2->task_info.current_state <= sonar2_compute;
  int sonar2_num = sonar2_check ? t_sonar2->task_info.deadline : int_max;

#if debug_verbos
  char temp_str[50];
  sprintf(temp_str, "control check = %s, cnt_num = %d\n", cnt_check ? "true" : "false", cnt_num);
  Serial.print(temp_str);
  sprintf(temp_str, "Sonar 0 check = %s, sonar0_num = %d\n", sonar0_check ? "true" : "false", sonar0_num);
  Serial.print(temp_str);
  sprintf(temp_str, "Sonar 1 check = %s, sonar1_num = %d\n", sonar1_check ? "true" : "false", sonar1_num);
  Serial.print(temp_str);
  sprintf(temp_str, "Sonar 2 check = %s, sonar2_num = %d\n", sonar2_check ? "true" : "false", sonar2_num);
  Serial.print(temp_str);
#endif

  // on a tie t_cnt -> sonar0 -> sonar1 -> sonar2
  if (cnt_num <= sonar0_num && cnt_num <= sonar1_num && 
      cnt_num <= sonar2_num && cnt_check){ 
        //Control has the closest deadline
#if debug
    Serial.println("control is running");
#endif
    run_cnt(t_control,dir_info,
              t_sonar0->distance,t_sonar1->distance,t_sonar2->distance);
              
  }else if(sonar0_num <= sonar1_num && sonar0_num <= sonar1_num &&
            sonar0_check){ 
              // sonar0 has the closest deadline
#if debug
    Serial.println("Sonar0 is running");
#endif
    run_ping(sonar0_trig, sonar0_echo, t_sonar0);
  }else if(sonar1_num <= sonar2_num && sonar1_check){ // sonar1 has the closest deadline
#if debug
    Serial.println("Sonar1 is running");
#endif
    run_ping(sonar1_trig, sonar1_echo, t_sonar1);
  }else if(sonar2_check){// sonar2 has the closest deadline
#if debug
    Serial.println("Sonar2 is running");
#endif
    run_ping(sonar2_trig, sonar2_echo, t_sonar2);
  }else {
#if debug
    Serial.println("No task is running");
#endif
  }

}

void calculate_manditory(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             int task_idx){

  //TODO FIGURE OUT THIS
        
}

void update_tasks(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             int task_idx){

  update_task(t_control,task_idx,control_period);
  update_task(&(t_sonar0->task_info),task_idx,sonar0_period);
  update_task(&(t_sonar1->task_info),task_idx,sonar1_period);
  update_task(&(t_sonar2->task_info),task_idx,sonar2_period); 

}

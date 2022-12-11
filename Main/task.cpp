#include "task.h"
#include "control_func.h"
#include "sonar_func.h"


void int_control(task* int_task){
  int_task->taskId = 69;
  int_task->current_state = 1;
  int_task->compute = control_compute;
  int_task->deadline += control_period;
  int_task->laxity = control_period - control_compute;

  //int as no misses
  for(int i = 0; i < control_k; i++){
    int_task->task_histoy[i] = 0;
  }
}
void int_sonar0(sonar_task* int_task){
  int_task->task_info.taskId = 0;
  int_task->task_info.current_state = 1;
  int_task->task_info.compute = sonar0_compute;
  int_task->task_info.deadline += sonar0_period;
  int_task->task_info.laxity = sonar0_period - sonar0_compute;
  
  //int as no misses
  for(int i = 0; i < sonar0_k; i++){
    int_task->task_info.task_histoy[i] = 0;
  }
}

void int_sonar1(sonar_task* int_task){
  int_task->task_info.taskId = 1;
  int_task->task_info.current_state = 1;
  int_task->task_info.compute = sonar0_compute;
  int_task->task_info.deadline += sonar0_period;
  int_task->task_info.laxity = sonar0_period - sonar0_compute;
    
  //int as no misses
  for(int i = 0; i < sonar1_k; i++){
    int_task->task_info.task_histoy[i] = 0;
  }
}

void int_sonar2(sonar_task* int_task){
  int_task->task_info.taskId = 2;
  int_task->task_info.current_state = 1;
  int_task->task_info.compute = sonar0_compute;
  int_task->task_info.deadline += sonar0_period;
  int_task->task_info.laxity = sonar0_period - sonar0_compute;
    
  //int as no misses
  for(int i = 0; i < sonar2_k; i++){
    int_task->task_info.task_histoy[i] = 0;
  }
}

void int_direction(direction_info* int_task){
  int_task->x = 0;
  int_task->y = 0;
  int_task->angle = 0;
  int_task->turn_left = false;
  int_task->turn_right = false;
}

void update_task(task* update_task,long idx,int period, short k, short miss_allowed){
  if(idx == update_task->deadline){
    if(update_task->current_state < update_task->compute){
      // Missed deadline
      update_miss_history(update_task, k, 1);
    }else{
      // Hit deadline
      update_miss_history(update_task, k, 0);
    }

    if(miss_allowed - update_task->task_sum > 0){
      update_task->mandatory = false;
    }else{
      update_task->mandatory = true;
      if(miss_allowed - update_task->task_sum < 0){
         Serial.print("(ERROR) We missed more that m of the last k tasks for id ");
         Serial.println(update_task->taskId,idx);
      }
    }
    
    reset_task(update_task, period);

#if debug
  char temp_str[35];
  sprintf(temp_str, "Tast %d reset at index %d\n", update_task->taskId,idx);
  Serial.print(temp_str); 
#endif
#if debug_verbos
  char temp_str_2[35];
  sprintf(temp_str, "This task %s it's deadline.\nThis upcoming task is %s.\n",
          update_task->current_state < update_task->compute ? "missed" : "hit",
          update_task->mandatory ? "Mandatory" : "Optional");
  
#endif
  }else{
    update_task->laxity -= 1;
  }
}

void reset_task(task* rst_task, int period){
  rst_task->current_state = 1;
  rst_task->deadline += period;
  rst_task->laxity = period - rst_task->compute;
}

void update_miss_history(task* update_task, short k, byte hit){
  short task_sum = 0;
  for(int i = k-1; i > 0; i--){
    update_task->task_histoy[i] = update_task->task_histoy[i-1];
    task_sum += update_task->task_histoy[i];
  }
  update_task->task_histoy[0] = hit;
  task_sum += hit;
  update_task->task_sum = task_sum;
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
  sprintf(temp_str, "control check = %s, cnt_num = %d, Manditory = %s\n", 
          cnt_check ? "true" : "false", cnt_num, t_control->mandatory ? "true" : "false");
  Serial.print(temp_str);
  sprintf(tecnt_checkmp_str, "Sonar 0 check = %s, sonar0_num = %d, Manditory = %s\n",
          sonar0_check ? "true" : "false", sonar0_num, t_sonar0->task_info.mandatory ? "true" : "false");
  Serial.print(temp_str);
  sprintf(temp_str, "Sonar 1 check = %s, sonar1_num = %d, Manditory = %s\n",
          sonar1_check ? "true" : "false", sonar1_num, t_sonar1->task_info.mandatory ? "true" : "false");
  Serial.print(temp_str);
  sprintf(temp_str, "Sonar 2 check = %s, sonar2_num = %d, Manditory = %s\n",
          sonar2_check ? "true" : "false", sonar2_num, t_sonar2->task_info.mandatory ? "true" : "false");
  Serial.print(temp_str);
#endif

  bool control_pass = t_control->mandatory;
  bool sonar0_pass = t_sonar0->task_info.mandatory;
  bool sonar1_pass = t_sonar1->task_info.mandatory;
  bool sonar2_pass = t_sonar2->task_info.mandatory;
  
  for(int i = 0; i < 2; i++){
    if(i == 1 || 
        ~(control_pass || sonar0_pass || sonar1_pass || sonar2_pass)){
      //None of the manditory tasks ran or there are not manditory tasks.  
      control_pass = true;
      sonar0_pass = true;
      sonar1_pass = true;
      sonar2_pass = true;
    }
        
    // on a tie t_cnt -> sonar0 -> sonar1 -> sonar2
    if (cnt_num <= sonar0_num && cnt_num <= sonar1_num && 
        cnt_num <= sonar2_num && cnt_check && control_pass){ 
          //Control has the closest deadline
#if debug
  Serial.println("control is running");
#endif
      run_cnt(t_control,dir_info,
                t_sonar0->distance,t_sonar1->distance,t_sonar2->distance);
                
    }else if(sonar0_num <= sonar1_num && sonar0_num <= sonar1_num &&
              sonar0_check && sonar0_pass){ 
                // sonar0 has the closest deadline
#if debug
  Serial.println("Sonar0 is running");
#endif
      run_ping(sonar0_trig, sonar0_echo, t_sonar0);
    }else if(sonar1_num <= sonar2_num && sonar1_check && sonar1_pass){ // sonar1 has the closest deadline
#if debug
  Serial.println("Sonar1 is running");
#endif
      run_ping(sonar1_trig, sonar1_echo, t_sonar1);
    }else if(sonar2_check & sonar2_pass){// sonar2 has the closest deadline
#if debug
  Serial.println("Sonar2 is running");
#endif
      run_ping(sonar2_trig, sonar2_echo, t_sonar2);
    }
  }
}

void update_tasks(task* t_control,sonar_task* t_sonar0,
             sonar_task* t_sonar1,sonar_task* t_sonar2,
             long task_idx){

  update_task(t_control,task_idx,control_period,control_k,control_k-control_m);
  update_task(&(t_sonar0->task_info),task_idx,sonar0_period,sonar0_k,sonar0_k-sonar0_m);
  update_task(&(t_sonar1->task_info),task_idx,sonar1_period,sonar0_k,sonar1_k-sonar1_m);
  update_task(&(t_sonar2->task_info),task_idx,sonar2_period,sonar0_k,sonar2_k-sonar2_m); 

}

#include "control_func.h"

void run_cnt(task* my_task,direction_info* dir_info,
              int sonar0, int sonar1,int sonar2){
#if debug_verbos
  Serial.print("Starting run_cnt at state ");
  Serial.println(my_task->current_state);
#endif
       
  switch(my_task->current_state){
    case 1: //Process response
      process_response(my_task,dir_info,sonar0,sonar1,sonar2);
      my_task->current_state = 2;
      break;

    case 2: // Update Wheels
      update_wheels(my_task,dir_info);
      my_task->current_state = 3;
      break;
      
    default:
      Serial.println("(ERROR) control is in the default");
      break;
  }
}

void process_response(task* my_task,direction_info* dir_info,
              int sonar0_dist, int sonar1_dist,int sonar2_dist){
  bool fwd_hit = false;
  bool left_hit = false;
  bool right_hit = false;
  
  //forward
  if(sonar0_dist > 5 && sonar0_dist < 50){
    fwd_hit = true;
  }
  //left
  if(sonar1_dist > 5 && sonar1_dist < 50){
    left_hit = true;
  }
  //right
  if(sonar2_dist > 5 && sonar2_dist < 40){
    right_hit = true;
  }

#if debug_wheels
  char str_temp[80];
  sprintf(str_temp, "Sonar0 dist = %d, Sonar1 dist = %d, Sonar2 _dist = %d\n",
          sonar0_dist, sonar1_dist, sonar2_dist);
  Serial.print(str_temp);
  sprintf(str_temp, "Starting process_response\nfwd was a %s, left was a %s, right was a %s\n",
          fwd_hit ? "hit" : "miss",
          left_hit ? "hit" : "miss",
          right_hit ? "hit" : "miss");
  Serial.print(str_temp);
#endif
  //Moving forward
  if(fwd_hit){
    //To the right of center
    if(dir_info->angle > 0 && !(dir_info->turn_left)){
      //If right of the center, default going left
      if(left_hit){ 
        dir_info->turn_right = true;
        dir_info->turn_left = false;
        dir_info->angle += 1;
      }else{
        dir_info->turn_left = true;
        dir_info->turn_right = false;
        dir_info->angle -= 1;
      }
      return;
    }else{
      //If left of the center, default going right
      if(right_hit){
        dir_info->turn_left = true;
        dir_info->turn_right = false;
        dir_info->angle -= 1;
      }else{
        dir_info->turn_right = true;
        dir_info->turn_left = false;
        dir_info->angle += 1;
      }
      return;
    }
  }

  if(sonar1_dist > 5 && sonar1_dist < 25){ 
    dir_info->turn_right = true;
    dir_info->turn_left = false;
    dir_info->angle += 1;
    return;
  }
  if(sonar2_dist > 5 && sonar2_dist < 25){
    dir_info->turn_left = true;
    dir_info->turn_right = false;
    dir_info->angle -= 1;
    return;
  }
  dir_info->turn_right = false;
  dir_info->turn_left = false;

#if debug_wheels
  sprintf(str_temp, "Turn Left = %s, Turn Right = %s, Dir = %d\n",
          dir_info->turn_left ? "Yes" : "No",
          dir_info->turn_right ? "Yes" : "No",
          dir_info->angle);
  Serial.print(str_temp);
#endif   
}

void update_wheels(task* my_task,direction_info* dir_info){
  if(dir_info->turn_right && dir_info->turn_left){
    Serial.print("(ERROR) trying to turn both left and right\n");
    stop_wheels();
    return;
  }
  
  if(dir_info->turn_right){
#if debug_verbos
  Serial.print("Turning Right\n");
#endif
      turn_right();
      return;
  }
  
  if(dir_info->turn_left){
#if debug_verbos
  Serial.print("Turning Left\n");
#endif
      turn_left();
      return;
  }

  go_forward();
}

void stop_wheels(){
  digitalWrite(left_wheel_pin, LOW);
  digitalWrite(right_wheel_pin, LOW);
}

void turn_right(){
  digitalWrite(left_wheel_pin, LOW);
  digitalWrite(right_wheel_pin, HIGH);
}

void turn_left(){
  digitalWrite(left_wheel_pin, HIGH);
  digitalWrite(right_wheel_pin, LOW);
}

void go_forward(){
  digitalWrite(left_wheel_pin, HIGH);
  digitalWrite(right_wheel_pin, HIGH);
}

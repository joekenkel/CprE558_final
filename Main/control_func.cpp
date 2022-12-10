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
  if(sonar0_dist > 5 && sonar0_dist < 100){
    fwd_hit = true;
  }
  //left
  if(sonar1_dist > 5 && sonar1_dist < 100){
    left_hit = true;
  }
  //right
  if(sonar2_dist > 5 && sonar2_dist < 100){
    right_hit = true;
  }

#if debug_verbos
  char str_temp[80];
  sprintf(str_temp, "Starting process_response\nfwd was a %s, left was a %s, right was a %s\n",
          fwd_hit ? "hit" : "miss",
          left_hit ? "hit" : "miss",
          right_hit ? "hit" : "miss");
  Serial.print(str_temp);
#endif

  //Moving Right
  if(dir_info->angle == 45){
    if(left_hit && fwd_hit){
      dir_info->turn_right = true;
      return;
    }else if(left_hit){
      return;
    }else{
      dir_info->turn_left = true;
    }
  }
  //Moving Left
  if(dir_info->angle == -45){
    if(right_hit && fwd_hit){
      dir_info->turn_left = true;
      return;
    }else if(right_hit){
      return;
    }else{
      dir_info->turn_right = true;
    }
  }

  //Moving forward
  if(fwd_hit){
    if(dir_info->y > 0){
      //If right of the center, default going left
      if(left_hit){ 
        dir_info->turn_right = true;
      }else{
        dir_info->turn_left = true;
      }
    }else{
      //If left of the center, default going right
      if(right_hit){
        dir_info->turn_left = true;
      }else{
        dir_info->turn_right = true;
      }
    }
  }

#if debug_verbos
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
      delayMicroseconds(turn_time);
      go_forward();
  }
  
  if(dir_info->turn_left){
#if debug_verbos
  Serial.print("Turning Left\n");
#endif
      turn_left();
      delayMicroseconds(turn_time);
      go_forward();
  }
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

#include "sonar_func.h"

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

    case 2: // Update Control
      
      my_task->current_state = 3;
      break;

    case 3: // Update Wheels 
      
      my_task->current_state = 4;
      break;
      
    default:
      Serial.println("control is in the default");
      break;
  }
  
}

void process_response(task* my_task,direction_info* dir_info,
              int sonar0_dist, int sonar1_dist,int sonar2_dist){
  bool fwd_hit = false;
  bool left_hit = false;
  bool right_hit = false;
  
  //forward
  if(sonar0_dist > 5 && sonar0_dist < 200){
    fwd_hit = true;
  }
  //left
  if(sonar1_dist > 5 && sonar1_dist < 200){
    left_hit = true;
  }
  //right
  if(sonar2_dist > 5 && sonar2_dist < 200){
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

void run_ping(short trig_pin, short echo_pin,sonar_task* my_task){
#if debug_verbos
  Serial.print("Looking at Ping");
  Serial.println(my_task->task_info.taskId);
  Serial.print("Starting run_ping at state ");
  Serial.println(my_task->task_info.current_state);
#endif
  switch(my_task->task_info.current_state){
    case 1: // record duration
      ping_state(trig_pin, echo_pin, &(my_task->duration));
      my_task->task_info.current_state = 2;
      break;
      
    case 2: // Compute Distance
      compute_distance(&(my_task->duration),&(my_task->distance));
      my_task->task_info.current_state = 3;
      break;
      
    default:
      char buffer[40];
      sprintf(buffer, "Sonar %d is in the default", my_task->task_info.taskId);
      Serial.println(buffer);
      break;
    
  }

}


void ping_state(short trig_pin, short echo_pin, long* duration){
#if debug_verbos
  Serial.println("Running Ping_state");
#endif
  trigger_sonar(trig_pin);
  *duration = pulseIn(echo_pin, HIGH);
}

void compute_distance(long* duration,int* distance){
  *distance = *duration * 0.034 / 2;
#if debug_verbos
  Serial.println("Running compute_distance");
  Serial.print("Time: ");
  Serial.print(*duration);
  Serial.print(" uS\nDistance: ");
  Serial.print(*distance);
  Serial.println(" cm");
#endif
}

void trigger_sonar(short trig_pin){
  // Clears the trigPin
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
}

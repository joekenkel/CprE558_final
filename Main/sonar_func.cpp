#include "sonar_func.h"

void run_cnt(task* my_task){
  switch(my_task->current_state){
    case 1: //Process response
      
      my_task->current_state = 2;
      break;

    case 2: // Update Control
      my_task->current_state = 3;
      break;

    case 3: // Update Wheels 
      my_task->current_state = 4;
      break;

    case 4:
      // wait here
      break;

    default:
      Serial.println("control is in the default");
      break;
  }
  
}

void run_ping(short trig_pin, short echo_pin,sonar_task* my_task){
  
  switch(my_task->task_info.current_state){
    case 1: // record duration
      ping_state(trig_pin, echo_pin, &(my_task->duration));
      my_task->task_info.current_state = 2;
      break;
      
    case 2: // Compute Distance
      compute_distance(&(my_task->duration),&(my_task->distance));
      my_task->task_info.current_state = 3;
      break;
      
    case 3: // Wait state
      break;
      
    default:
      char buffer[40];
      sprintf(buffer, "Sonar %d is in the default", my_task->task_info.taskId);
      Serial.println(buffer);
      break;
    
  }

}


void ping_state(short trig_pin, short echo_pin, long* duration){
  trigger_sonar(trig_pin);
  *duration = pulseIn(echo_pin, HIGH);
}

void compute_distance(long* duration,int* distance){
  Serial.print("Time: ");
  Serial.println(*duration);
  *distance = *duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(*distance);
  Serial.println(" cm");
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

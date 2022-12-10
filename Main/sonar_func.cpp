#include "sonar_func.h"

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
      sprintf(buffer, "(ERROR)Sonar %d is in the default", my_task->task_info.taskId);
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

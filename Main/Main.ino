#include "sonar_func.h"
#include "task.h"
#include "types.h"

task t_control;
sonar_task t_sonar0;
sonar_task t_sonar1;
sonar_task t_sonar2;

unsigned long nxt_task_time;
int task_idx;

void setup() {
  //Straight Forward
  t_sonar0.task_info.taskId = 0;
  reset_sonar0(&t_sonar0);
  pinMode(sonar0_trig, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(sonar0_echo, INPUT); // Sets the echoPin as an INPUT

  //Left
  t_sonar0.task_info.taskId = 1;
  reset_sonar1(&t_sonar1);
  pinMode(sonar1_trig, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(sonar1_echo, INPUT); // Sets the echoPin as an INPUT

  //Right
  t_sonar0.task_info.taskId = 2;
  reset_sonar2(&t_sonar2);
  pinMode(sonar2_trig, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(sonar2_echo, INPUT); // Sets the echoPin as an INPUT

  t_control.taskId = 2;
  reset_control(&t_control);
  
  Serial.begin(9600); // Starts the serial communication
  Serial.println("Debug Print 1");

  task_idx = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  nxt_task_time = micros() + time_interal*1000;

  calculate_manditory(&t_control,&t_sonar0,&t_sonar1,&t_sonar2,task_idx);
  sel_task(&t_control,&t_sonar0,&t_sonar1,&t_sonar2,task_idx);
  task_idx += 1;
  
  while(micros() < nxt_task_time){}
  
}

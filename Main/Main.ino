#include "sonar_func.h"
#include "control_func.h"
#include "task.h"
#include "types.h"
#include <string.h>

task t_control;
sonar_task t_sonar0;
sonar_task t_sonar1;
sonar_task t_sonar2;
direction_info dir_info;

unsigned long nxt_task_time;
long task_idx;

void setup() {
  //Straight Forward
  int_sonar0(&t_sonar0);
  pinMode(sonar0_trig, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(sonar0_echo, INPUT); // Sets the echoPin as an INPUT

  //Left
  int_sonar1(&t_sonar1);
  pinMode(sonar1_trig, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(sonar1_echo, INPUT); // Sets the echoPin as an INPUT

  //Right
  int_sonar2(&t_sonar2);
  pinMode(sonar2_trig, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(sonar2_echo, INPUT); // Sets the echoPin as an INPUT

  //wheels
  int_control(&t_control);
  pinMode(left_wheel_pin, OUTPUT);  // Sets the left_wheel_pin as an OUTPUT
  pinMode(right_wheel_pin, OUTPUT); // Sets the right_wheel_pin as an OUTPUT
  
  int_direction(&dir_info);
  
  Serial.begin(9600); // Starts the serial communication
  Serial.println("Debug Verison 3");

  task_idx = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
#if debug_time
  char str_temp[100];
  sprintf(str_temp, "\n\nStarting Task %d\n", task_idx);
  Serial.print(str_temp);
#endif 

  unsigned long start_time = micros();
  nxt_task_time = start_time + time_interal*1000;

  sel_task(&t_control,&t_sonar0,&t_sonar1,&t_sonar2,&dir_info);
  task_idx += 1;
#if debug_time
  unsigned long cmp_time = micros();
#endif
  while(micros() < nxt_task_time){}
  update_tasks(&t_control,&t_sonar0,&t_sonar1,&t_sonar2,task_idx);

#if debug_time
  sprintf(str_temp, "Laxity = %lu uS\n", (cmp_time - start_time));
  int i;
  if(strlen(str_temp) > 15){
    for(i = strlen(str_temp)+1;i >= strlen(str_temp)-8;i--){
      str_temp[i+1]=str_temp[i];
    }
    str_temp[i+1] = ',';
  }
 
  Serial.print(str_temp);
  delay(1000);
#endif
}

#ifndef TYPES_H
#define TYPES_H

#define debug_verbos 0
#define debug 0
#define int_max 32767

#define time_interal 10    // ms
#define turn_time 5000     // us

#define control_compute 3  // count
#define control_period 8   // count
#define control_m 3        // count
#define control_k 4        // count
#define left_wheel_pin 8   // pin number
#define right_wheel_pin 9  // pin number

#define sonar0_compute 2  // count
#define sonar0_period 12  // count
#define sonar0_m 3        // count
#define sonar0_k 4        // count
#define sonar0_trig 1     // pin number
#define sonar0_echo 0     // pin number

#define sonar1_compute 2  // count
#define sonar1_period 12  // count
#define sonar1_m 3        // count
#define sonar1_k 4        // count
#define sonar1_trig 2     // pin number
#define sonar1_echo 3     // pin number

#define sonar2_compute 2  // count
#define sonar2_period 12  // count
#define sonar2_m 3        // count
#define sonar2_k 4        // count
#define sonar2_trig 2     // pin number
#define sonar2_echo 3     // pin number

struct task{
  short taskId;
  short current_state;
  short compute;    // task count
  short deadline;   // task count
  short laxity;     // task count
  
  bool mandatory; // 1 = mandatory, 0 = optional
};

struct sonar_task{             
  task task_info;    //basic task information
  
  long duration;  // mS
  int distance;   // cm
};

struct direction_info{
  int x;
  int y;
  int angle;
  bool turn_left;
  bool turn_right;
};

#endif

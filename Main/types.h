#ifndef TYPES_H
#define TYPES_H

#define time_interal 1    // 1 ms

#define contol_compute 3  // count
#define contol_period 8   // count
#define contol_m 3        // count
#define contol_k 4        // count

#define sonar0_compute 2  // count
#define sonar0_period 12  // count
#define sonar0_m 3        // count
#define sonar0_k 4        // count
#define sonar0_trig 2     // pin number
#define sonar0_echo 3     // pin number

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

#endif

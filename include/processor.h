#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cmath>
#include "linux_parser.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
   
   float Utilization();
   void set_idle(int idle){ idle_ = idle;};
   void set_non_idle(int nonidle){ nonidel_ = nonidle;};
   void set_current_utilization();   

 private:
   int pre_idle_    = 0;
   int pre_nonidel_ = 0;
   int idle_        = 0;
   int nonidel_     = 0;
     enum Cpu_stats_ {user = 0, 
                   nice, 
                   system,
                   idle,
                   iowait,
                   irq,
                   softirq,
                   steal};
};

#endif
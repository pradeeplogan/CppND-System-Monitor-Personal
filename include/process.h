#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
#include <math.h>  
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  void set_pid(const int pid);
  void set_cmd(const std::string);
  void set_usr_info(const std::string);
  void set_mem(const std::string);
  void set_uptime(const long int);
  // TODO: Declare any necessary private members
  enum process_uti {utime = 0, stime, cutime, cstime, starttime};
 private:
 int pid_;
 std::string _cmd;
 std::string _usr_info;
 std::string _mem_size;
 long int _uptime;
 float _cpu_uti;
 std::vector<int> _process_uti_component;
};
#endif
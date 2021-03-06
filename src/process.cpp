#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid()
{ 
    return pid_;
}

// Return this process's Average CPU utilization
float Process::CpuUtilization()
{ 
    int total_time;
    long int seconds;
    _process_uti_component = std::move(LinuxParser::ProcessUtilization(pid_));
        
    total_time =  _process_uti_component[utime] + _process_uti_component[stime] +
                  _process_uti_component[cutime] + _process_uti_component[cstime];

    seconds    = _uptime - (_process_uti_component[starttime]/sysconf(_SC_CLK_TCK));

    _cpu_uti   = (float((total_time/sysconf(_SC_CLK_TCK))) / seconds);
    if (isnan(_cpu_uti)) {
        return 0.0;
    }
    return  _cpu_uti;
}

// Return the command that generated this process
string Process::Command()
{ 
    return _cmd; 
}

// TODO: Return this process's memory utilization
string Process::Ram() 
{
    _mem_size = std::to_string(std::stoi(LinuxParser::Ram(pid_))/1000);
     return _mem_size; 
}

//Return the user (name) that generated this process
string Process::User()
{ 
    return _usr_info;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime()
{ 
    _uptime = LinuxParser::UpTime() - LinuxParser::UpTime(pid_); 
    return _uptime;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

// Sets process's ID
void Process::set_pid(const int pid)
{
    pid_ = pid;
}

// Sets process cmd line
void Process::set_cmd(const std::string cmd)
{
    _cmd = cmd;
}

void Process::set_usr_info(const std::string usr_info)
{
    _usr_info = usr_info;
}

void Process::set_mem(const std::string mem_size)
{
    _mem_size = std::to_string(std::stoi(mem_size)/1000);
}

void Process::set_uptime(const long int uptime)
{
    _uptime = uptime;
}
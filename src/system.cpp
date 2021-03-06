#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

//Return the system's CPU
Processor& System::Cpu() 
{       
    return cpu_;
}
// Return a container composed of the system's processes
vector<Process>& System::Processes()
{
    vector<int> pid = LinuxParser::Pids(); 
    int pid_exist   = 0;
    Process temp;

    for (auto i : pid) {
        for (auto j : processes_) {
        
            if (i == j.Pid()) {
                pid_exist = 1;
                break;
            }
        }

        if (!pid_exist) {
            temp.set_pid(i);
            temp.set_cmd(LinuxParser::Command(i));
            temp.set_usr_info(LinuxParser::User(std::stoi(LinuxParser::Uid(i))));
            temp.set_mem(LinuxParser::Ram(i));
            temp.set_uptime(LinuxParser::UpTime(i));
            processes_.push_back(temp);
            pid_exist = 0;
        }
        
    }
    return processes_;    
}

// Return the system's kernel identifier (string)
std::string System::Kernel()
{
    return LinuxParser::Kernel(); 
}

// Return the system's memory utilization
float System::MemoryUtilization()
{
    return LinuxParser::MemoryUtilization();
}

// Return the operating system name
std::string System::OperatingSystem()
{ 
    return LinuxParser::OperatingSystem(); 
}

// Return the number of processes actively running on the system
int System::RunningProcesses()
{
     return LinuxParser::RunningProcesses(); 
}

//Return the total number of processes on the system
int System::TotalProcesses()
{ 
    return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long System::UpTime()
{
    return LinuxParser::UpTime(); 
}
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
    // vector<string> cpu_info;
    // int idle;
    // int nonidle;

    // cpu_info = LinuxParser::CpuUtilization();

    // idle = std::stoi(cpu_info[Cpu_stats_::idle],nullptr,0)
    //      + std::stoi(cpu_info[Cpu_stats_::iowait],nullptr,0);

    // nonidle = std::stoi(cpu_info[Cpu_stats_::user],nullptr,0)
    //         + std::stoi(cpu_info[Cpu_stats_::nice],nullptr,0)
    //         + std::stoi(cpu_info[Cpu_stats_::system],nullptr,0)            
    //         + std::stoi(cpu_info[Cpu_stats_::irq],nullptr,0)
    //         + std::stoi(cpu_info[Cpu_stats_::softirq],nullptr,0)
    //         + std::stoi(cpu_info[Cpu_stats_::steal],nullptr,0);

    // cpu_.set_idle(idle);
    // cpu_.set_non_idle(nonidle);
    // cpu_.Utilization();      
    return cpu_;
}
/*
PrevIdle = previdle + previowait
Idle = idle + iowait

PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
NonIdle = user + nice + system + irq + softirq + steal

PrevTotal = PrevIdle + PrevNonIdle
Total = Idle + NonIdle

# differentiate: actual value minus the previous one
totald = Total - PrevTotal
idled = Idle - PrevIdle

CPU_Percentage = (totald - idled)/totald



*/
// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

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
#include "processor.h"

//Return the aggregate CPU utilization
float Processor::Utilization()
{   
    int pre_total;
    int total;
    int totald;
    int idled;

    Processor::set_current_utilization();

    pre_total = pre_idle_ + pre_nonidel_;
    total     = idle_     + nonidel_;

    totald    = std::abs(total - pre_total);
    idled     = std::abs(idle_ - pre_idle_);

    // pre_total = pre_nonidel_;
    // total     = nonidel_;

    // totald    = std::abs(total - pre_total);
    // idled     = std::abs(nonidel_ - pre_nonidel_);

    pre_idle_    = idle_;
    pre_nonidel_ = nonidel_;

    if (totald == 0) {
        if (pre_total != 0) 
            return 0.2;//float((pre_total - pre_idle_)/pre_total);
        else 
            return 0.11;      
    }

    return float(float(totald- idled)/float(totald));
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

void Processor::set_current_utilization()
{
    vector<string> cpu_info;
    cpu_info = LinuxParser::CpuUtilization();

    idle_ = std::stoi(cpu_info[Cpu_stats_::idle],nullptr,0)
            + std::stoi(cpu_info[Cpu_stats_::iowait],nullptr,0);

    nonidel_ = std::stoi(cpu_info[Cpu_stats_::user],nullptr,0)
            + std::stoi(cpu_info[Cpu_stats_::nice],nullptr,0)
            + std::stoi(cpu_info[Cpu_stats_::system],nullptr,0)            
            + std::stoi(cpu_info[Cpu_stats_::irq],nullptr,0)
            + std::stoi(cpu_info[Cpu_stats_::softirq],nullptr,0)
            + std::stoi(cpu_info[Cpu_stats_::steal],nullptr,0);
}

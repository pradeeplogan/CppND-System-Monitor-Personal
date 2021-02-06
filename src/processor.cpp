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

    pre_idle_    = idle_;
    pre_nonidel_ = nonidel_;

    return float(float(totald- idled)/float(totald));
}

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

#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, vertion;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> vertion;
  }
  return vertion;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
// system memory utilization = total_memory - free_memory
float LinuxParser::MemoryUtilization()
{
  string key;
  string line;
  string total_mem_str;
  string free_mem_str;
  string value;
  int    total_mem;
  int    free_mem;
   std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
        linestream >> key >> value;

        if (key == "MemTotal:") {
          total_mem_str = value;
          total_mem = std::stoi(total_mem_str, nullptr, 0);
        }

        if (key == "MemFree:") {
          free_mem_str = value;
          free_mem = std::stoi(free_mem_str, nullptr, 0);

          if (total_mem <= 0.0) {
              return 0.0;
          }
          else {
            return (float(total_mem-free_mem)/float(total_mem));
          }
        }
    }
  }
  return 0.0; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime()
{
  string line;
  string uptime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    std::replace(line.begin(), line.end(), '.', ' ');
    linestream >> uptime;
  }
  return long(std::stoi(uptime, nullptr, 0));
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

//Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization()
{ 
  string cpu;
  string line;
  string str;
  vector<string> cpu_stat;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()) {
    std::getline(filestream,line);
    std::istringstream linestream(line);

    // cpu_stat[0] == CPU-user  unit::USER_HZ
    // cpu_stat[1] == CPU-nice
    // cpu_stat[2] == CPU-system
    // cpu_stat[3] == CPU-idle
    // cpu_stat[4] == CPU-iowait
    // cpu_stat[5] == CPU-irq
    // cpu_stat[6] == CPU-softirq
    // cpu_stat[7] == CPU-steal
    linestream >> cpu;
    for(int i = 0; i < 8; i++) {
      linestream >> str;
      cpu_stat.push_back(str);
    }
    return cpu_stat; 
  }
  return cpu_stat; 
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses()
{ 
  string key;
  string value;
  string line;
  std::ifstream filesystem(kProcDirectory + kStatFilename);
  if (filesystem.is_open()) {
    while(std::getline(filesystem,line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "processes") {
        linestream >> value;
        return std::stoi(value,nullptr,0);
      }
    }
  }
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{ 
  string key;
  string value;
  string line;
  std::ifstream filesystem(kProcDirectory + kStatFilename);
  if (filesystem.is_open()) {
    while(std::getline(filesystem,line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "procs_running") {
        linestream >> value;
        return std::stoi(value,nullptr,0);
      }
    }
  }
  return 0;
}

//Read and return the command associated with a process
string LinuxParser::Command(int pid)
{ 
  std::string cmd_string;
  std::string line;
  std::ifstream filesystem(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (filesystem.is_open()) {
    while(std::getline(filesystem,line)) {
      std::istringstream linestream(line);
      linestream >> cmd_string;
      return cmd_string;
    }
  }
  
  return cmd_string; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid)
{ 
  std::string line;
  std::string key;
  std::string value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream,line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmSize:") {
        return value;
      }
    }
  }
  return "0";
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid)
{ 
  std::string key;
  std::string value;
  std::string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream,line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        return value;
      }
    }
    
  }
  return "1000"; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) 
{
  std::string key;
  std::string usr_info;
  std::string line;
  std::string x;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream,line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> usr_info >> x >>key;
        if (std::stoi(key,nullptr,0) == pid) {
          return usr_info;
        }
      
    }
  }
   return "NONE"; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid)
{ 
  std::string value;
  std::string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream,line)) {
      std::istringstream linestream(line);
      for(int i = 0; i < 22; i++) {
        linestream >> value;
      }
      return (std::stol(value)/sysconf(_SC_CLK_TCK));
    }
  }
  return 0; 
}

std::vector<int> LinuxParser::ProcessUtilization(int pid)
{
  std::vector<int> temp;
  std::string value;
  std::string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  while (std::getline(filestream,line)) {
    std::istringstream linestream(line);
    for(int i = 0; i < 13 ; i++) {
      linestream >> value;
    }

    // temp = {utime, stime, cutime, cstime} in ticks 
    for(int i = 0; i < 4 ; ++i) { 
      linestream >> value;
      temp.push_back(std::stoi(value));
    }

    for(int i = 0; i < 4 ; ++i) {
      linestream >> value;
    }

    // temp == startime in ticks
    linestream >> value;
    temp.push_back(std::stoi(value));
    return temp;
  }
  return temp;
}
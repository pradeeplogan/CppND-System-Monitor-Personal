#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds)
{ 
    string HH;
    string MM;
    string SS;
    string result;

    HH      = std::to_string(int(seconds/3600));
    seconds = int(seconds%3600);
    MM      = std::to_string(int(seconds/60)); 
    seconds = int(seconds%60);
    SS      = std::to_string(int(seconds));;

    result  = HH +":" +MM +":"+SS;
    return string(result); 
}
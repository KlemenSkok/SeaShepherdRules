
// Logger.cpp

#include "Logger.hpp"



void Logger::Success(const char* msg) { // green
    std::cout << "\x1b[38;5;82m[Success]: \x1b[m" << msg << "\n";
}

void Logger::Status(const char* msg) { // blue
    std::cout << "\x1b[38;5;26m[Status]: \x1b[m" << msg << "\n";
}

void Logger::Warning(const char* msg) { // yellow
    std::cout << "\x1b[38;5;226m[Warning]: \x1b[m" << msg << "\n";
}

void Logger::Error(const char* msg) { // red
    std::cout << "\x1b[38;5;160m[Error]: \x1b[m" << msg << "\n";
}
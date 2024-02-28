
// Logger.hpp

#pragma once

#include <iostream>



class Logger {

public:

    static void Success(const char*);
    static void Status(const char*);
    static void Warning(const char*);
    static void Error(const char*);

};
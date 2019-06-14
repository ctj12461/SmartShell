#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <memory>
#include "Commands.h"

class Apis
{
public:
    Apis();
    ~Apis();

    static void message(std::ostream& os, std::string msg);
    static void repeat(std::shared_ptr<ICommands> executor, ArgumentsType cmd, size_t times);
    static void condition(std::shared_ptr<ICommands> executor, ArgumentsType cmd, bool result);
};


#pragma once

#include <vector>
#include <sstream>
#include <string>

class Processer
{
public:
    Processer();
    ~Processer();

    std::vector<std::string> split(string str, string delim);
};


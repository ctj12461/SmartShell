#pragma once

#include <vector>
#include <sstream>
#include <istream>
#include <string>

class Processer
{
public:
    Processer();
    ~Processer();

    std::string read(std::istream& is);
    std::vector<std::string> split(std::string str, std::string delim);
};


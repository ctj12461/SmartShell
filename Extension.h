#pragma once

#include <ostream>
#include <string>

#include "Commons.hpp"

class Extension
{
public:
    Extension();
    virtual ~Extension();

    virtual ExecResult exec(ArgumentsType args) = 0;
};

class MessageExtension : public Extension
{
public:
    MessageExtension(std::ostream& os, std::string msg) :OStream(os), Message(msg) {};
    ~MessageExtension() {};

    ExecResult exec(ArgumentsType args) override;
private:
    std::ostream& OStream;
    std::string Message;
};
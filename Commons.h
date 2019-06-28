#pragma once

#include <vector>
#include <functional>
#include <string>

enum class ExecCode
{
    Successful = 0, DefaultError = -1, ArgumentError = 1, CommandError = 2
};

class ExecResult
{
public:
    ExecResult(ExecCode code) :Code(code) {}
    bool successful() { return Code == ExecCode::Successful; }
    ExecCode code() { return Code; }
    int codeNumber() { return static_cast<int>(Code); }
private:
    ExecCode Code;
};

using ArgumentsType = std::vector<std::string>;
using FunctionType = std::function<ExecResult(ArgumentsType&)>;

ExecResult done();
ExecResult defaultError();
ExecResult argumentError();
ExecResult commandError();
ExecResult custom(int code);
ExecResult custom(ExecCode code);
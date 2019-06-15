#pragma once

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <memory>

class ICommands;
class CommandsTree;
class Task;
class ExecResult;

using ArgumentsType = std::vector<std::string>;
using FunctionType = std::function<ExecResult(ArgumentsType)>;

class ICommands
{
public:
    virtual ~ICommands() {};
    
    virtual ExecResult exec(std::vector<std::string>& args, size_t index) = 0;
};

class CommandsTree : public ICommands
{
public:
    template<typename ...Commands> CommandsTree(Commands... cmds);
    ~CommandsTree() {};

    ExecResult exec(std::vector<std::string>& args, size_t index) override;
    void insert(std::string name, std::shared_ptr<CommandsTree> subcmd);
    void insert(std::string name, std::shared_ptr<Task> subcmd);
    void insert(std::string name, FunctionType func);
private:
    std::map<std::string, std::shared_ptr<ICommands>> SubCommands;
};

class Task : public ICommands
{
public:
    
    Task(FunctionType func);
    Task() {};

    ExecResult exec(std::vector<std::string>& args, size_t index) override;
private:
    FunctionType Function;
};

class ExecResult
{
public:
    ExecResult(int code) :Code(code) {}
    bool successful() { return Code == 0; }
    int code() { return Code; }
    static const int SuccessfulCode = 0;
    static const int DefaultErrorCode = -1;
private:
    bool Code;
};

template<typename ...Commands>
inline CommandsTree::CommandsTree(Commands ...cmds){
    int a[] = { (insert(cmds.first, cmds.second),0)... };
}


#pragma once

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <memory>

#include "Commons.h"
#include "Extension.h"

class ICommands;
class CommandsTree;
class Task;
class ExecResult;

class ICommands
{
public:
    virtual ~ICommands() {};
    
    virtual ExecResult exec(const ArgumentsType&, std::size_t index) = 0;
    virtual void load(const std::vector<std::string>& path, std::size_t index, std::shared_ptr<Extension> extension) 
        = 0;
};

class CommandsTree : public ICommands
{
public:
    template<typename ...Commands> CommandsTree(Commands... cmds) {
        int a[] = { (insert(cmds.first, cmds.second),0)... };
    }
    template<> CommandsTree() {};

    ~CommandsTree() {};

    ExecResult exec(const ArgumentsType& args, size_t index) override;
    void load(const std::vector<std::string>& path, std::size_t index, std::shared_ptr<Extension> extension) override;
    
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

    ExecResult exec(const ArgumentsType& args, size_t index) override;
    void load(const std::vector<std::string>& path, std::size_t index, std::shared_ptr<Extension> extension) override {};
private:
    FunctionType Func;
};


class ExtendedTask : public ICommands
{
public:
    ExtendedTask(std::shared_ptr<Extension> extask) : ExTask(extask) {};
    ~ExtendedTask() {};

    ExecResult exec(const ArgumentsType& args, size_t index) override;
    void load(const std::vector<std::string>& path, std::size_t index, std::shared_ptr<Extension> extension) override {};
private:
    std::shared_ptr<Extension> ExTask;
};
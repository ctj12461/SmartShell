#pragma once

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <memory>

using ArgumentsType = std::vector<std::string>;
using FunctionType = std::function<void(ArgumentsType)>;

class ICommands
{
public:
    virtual ~ICommands() {};
    
    virtual void exec(std::vector<std::string>& args, size_t index) = 0;
};

class Task;

class CommandsTree : public ICommands
{
public:
    template<typename ...Commands> CommandsTree(Commands... cmds);
    ~CommandsTree() {};

    void exec(std::vector<std::string>& args, size_t index) override;
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

    void exec(std::vector<std::string>& args, size_t index) override;
private:
    FunctionType Function;
};

template<typename ...Commands>
inline CommandsTree::CommandsTree(Commands ...cmds){
    int a[] = { (insert(cmds.first, cmds.second),0)... };
}

template<typename Function>
std::pair<std::string, std::shared_ptr<Task>> makeTask(std::string name, Function func) {
    using namespace std;
    return make_pair(name, make_shared<Task>(func));
}

template<typename ...Commands>
std::pair<std::string, std::shared_ptr<CommandsTree>> makeCommandsTree(std::string name, Commands ...cmds) {
    using namespace std;
    return make_pair(name, make_shared<CommandsTree>(cmds...));
}
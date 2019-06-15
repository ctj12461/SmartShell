#include "stdafx.h"
#include "Commands.h"

using namespace std;

ExecResult CommandsTree::exec(std::vector<std::string>& args, size_t index) {
    while (index < args.size()) {
        auto i = SubCommands.find(args[index]);
        if (i != SubCommands.end()) {
            return i->second->exec(args, index + 1);
        }
        index++;
    }
}

void CommandsTree::insert(std::string name, std::shared_ptr<CommandsTree> subcmd){
    SubCommands.insert(make_pair(name, dynamic_pointer_cast<ICommands>(subcmd)));
}

void CommandsTree::insert(std::string name, std::shared_ptr<Task> subcmd) {
    SubCommands.insert(make_pair(name, dynamic_pointer_cast<ICommands>(subcmd)));
}

void CommandsTree::insert(std::string name, FunctionType func){
    shared_ptr<Task> taskptr;
    shared_ptr<ICommands> cmdptr;
    taskptr = make_shared<Task>(func);
    cmdptr = dynamic_pointer_cast<ICommands>(taskptr);
    if (cmdptr) {
        auto i = SubCommands.find(name);
        if (i == SubCommands.end()) {
            SubCommands.insert(make_pair(name, cmdptr));
        }else {
            SubCommands[name] = cmdptr;
        }
    }
}

Task::Task(FunctionType func) :Function(func) {

}

ExecResult Task::exec(std::vector<std::string>& args, size_t index){
    vector<string>::iterator i;
    if (index < args.size()) {
        vector<string> rawargs;
        for (size_t i = index; i < args.size(); i++) {
            rawargs.push_back(args[i]);
        }
        return Function(rawargs);
    }
}

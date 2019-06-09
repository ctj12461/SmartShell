#include "stdafx.h"
#include "Commands.h"

using namespace std;

void CommandsTree::exec(std::vector<std::string>& args, size_t index){
    for (pair<string, std::shared_ptr<ICommands>> i : SubCommands) {
        if (index < args.size() && i.first == args[index]) {
            i.second->exec(args, index + 1);
            break;
        }
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

void Task::exec(std::vector<std::string>& args, size_t index){
    vector<string>::iterator i;
    if (index < args.size()) {
        vector<string> rawargs;
        for (size_t i = index; i < args.size(); i++) {
            rawargs.push_back(args[i]);
        }
        Function(rawargs);
    }
}

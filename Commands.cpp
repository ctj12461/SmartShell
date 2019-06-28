#include "stdafx.h"
#include "Commands.h"

using namespace std;

ExecResult CommandsTree::exec(const ArgumentsType& args, size_t index) {
    while (index < args.size()) {
        auto i = SubCommands.find(args[index]);
        if (i != SubCommands.end()) {
            return i->second->exec(args, index + 1);
        }
        index++;
    }
    return commandError();
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

void CommandsTree::load(const vector<std::string>& path, size_t index, shared_ptr<Extension> extension) {
    if (index < path.size()) {
        auto i = SubCommands.find(path[index]);
        if (i != SubCommands.end()) {
            i->second->load(path, index + 1, extension);
        } else {
            SubCommands[path[index]] = dynamic_pointer_cast<ICommands>(make_shared<CommandsTree>());
            SubCommands[path[index]]->load(path, index + 1, extension);
        }
    }
    if (index == path.size() - 1) {
        SubCommands[path[index]].reset();
        SubCommands[path[index]] = dynamic_pointer_cast<ICommands>(make_shared<ExtendedTask>(extension));
    }
}

Task::Task(FunctionType func) :Func(func) {

}

ExecResult Task::exec(const ArgumentsType& args, size_t index){
    vector<string> rawargs;
    vector<string>::iterator i;
    if (index < args.size()) {
        copy(args.begin()+=index, args.end(), back_inserter(rawargs));
        return Func(rawargs);
    } else if (index == args.size()) {
        return Func(rawargs);
    } else {
        return argumentError();
    }
}

ExecResult ExtendedTask::exec(const ArgumentsType& args, size_t index) {
    vector<string>::iterator i;
    if (index < args.size()) {
        vector<string> rawargs;
        for (size_t i = index; i < args.size(); i++) {
            rawargs.push_back(args[i]);
        }
        return ExTask->exec(rawargs);
    } else {
        return argumentError();
    }
    
}

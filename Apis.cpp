#include "stdafx.h"
#include "Apis.h"

using namespace std;

Apis::Apis()
{
}


Apis::~Apis()
{
}

void Apis::message(std::ostream & os, std::string msg){
    os << msg;
}

void Apis::condition(std::shared_ptr<ICommands> executor, ArgumentsType cmd, bool result){
    if (result) {
        executor->exec(cmd, 0);
    }
}

void Apis::repeat(std::shared_ptr<ICommands> executor, ArgumentsType cmd, size_t times){
    for (size_t i = 1; i <= times; i++) {
        executor->exec(cmd, 0);
    }
}


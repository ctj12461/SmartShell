// tb.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <iostream>
#include "Commands.h"

using namespace std;

int main() {
    CommandsTree tree(
        makeCommandsTree("tree1", 
            makeTask("cmd1", [&](ArgumentsType args) {
                cout << "Tree1 - Command1 " << args[0] << endl;
            }),
            makeCommandsTree("tree2", 
                makeTask("cmd1", [&](ArgumentsType args) {
                    cout << "Tree1 - Tree2 - Command1 " << args[0] << endl;
                }),
                makeTask("cmd2", [&](ArgumentsType args) {
                    cout << "Tree1 - Tree2 - Command2 " << args[0] << endl;
                })
            )
        ),
        makeCommandsTree("tree2",
            makeTask("cmd1", [&](ArgumentsType args) {
                cout << "Tree2 - Command1 " << args[0] << endl;
            }),
            makeTask("cmd2", [&](ArgumentsType args) {
                cout << "Tree2 - Command2 " << args[0] << endl;
            })
        )
    );
            
    ArgumentsType args1 = { "tree1","cmd1","Hello World 1st" };
    ArgumentsType args2 = { "tree2","cmd2","Hello World 2nd" };
    ArgumentsType args3 = { "tree1","tree2","cmd2","Hello World 3nd" };
    tree.exec(args1, 0);
    tree.exec(args2, 0);
    tree.exec(args3, 0);
    return 0;
    
}


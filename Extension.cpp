#include "stdafx.h"
#include "Extension.h"

using namespace std;

Extension::Extension() {
}


Extension::~Extension() {
}

ExecResult MessageExtension::exec(ArgumentsType args) {
    OStream << Message << " " << args[0] << endl;
    return done();
}

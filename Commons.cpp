#include "stdafx.h"
#include "Commons.h"

ExecResult done() {
    return ExecResult(ExecCode::Successful);
}

ExecResult defaultError() {
    return ExecResult(ExecCode::DefaultError);
}

ExecResult argumentError() {
    return ExecResult(ExecCode::ArgumentError);
}

ExecResult commandError() {
    return ExecResult(ExecCode::CommandError);
}

ExecResult custom(int code) {
    return ExecResult(static_cast<ExecCode>(code));
}

ExecResult custom(ExecCode code) {
    return ExecResult(code);
}

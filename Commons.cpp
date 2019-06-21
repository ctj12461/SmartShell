#include "stdafx.h"
#include "Commons.hpp"

ExecResult done() {
    return ExecResult(ExecResult::SuccessfulCode);
}

ExecResult error() {
    return ExecResult(ExecResult::DefaultErrorCode);
}
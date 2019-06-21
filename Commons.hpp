#include <vector>
#include <functional>
#include <string>

using ArgumentsType = std::vector<std::string>;
using FunctionType = std::function<ExecResult(ArgumentsType&)>;

class ExecResult
{
public:
    ExecResult(int code) :Code(code) {}
    bool successful() { return Code == 0; }
    int code() { return Code; }
    static const int SuccessfulCode = 0;
    static const int DefaultErrorCode = -1;
private:
    bool Code;
};

ExecResult done();

ExecResult error();
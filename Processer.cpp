#include "stdafx.h"
#include "Processer.h"

using namespace std;

Processer::Processer()
{
}

Processer::~Processer()
{
}

std::string Processer::read(std::istream & is){
    string str;
    getline(is, str);
    return str;
}

vector<string> Processer::split(string str, string delim) {
    vector<string> arr;
    string tem;
    for (char& i : str) {
        if (delim.find(i) != -1) {
            i = '\a';
        }
    }
    stringstream ss(str);
    char del = '\a';
    while (getline(ss, tem, del)) {
        if (tem != "") {
            arr.push_back(tem);
        }
    }
    return arr;
}

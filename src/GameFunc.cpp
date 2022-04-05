#include "GameFunc.h"

string longLongToString(long long x){
    stringstream ss;
    ss << x;
    string str = ss.str();
    return str;
}

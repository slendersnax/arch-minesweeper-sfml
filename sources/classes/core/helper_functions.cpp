#include "helper_functions.h"

std::string intToString(int n) {
    if(n == 0)
        return "0";
    
    std::string resultReverse;
    std::string result;

    while(n > 0) {
        resultReverse += static_cast<char>(n % 10 + '0');
        n /= 10;
    }

    int len = resultReverse.length();
    for(int i = 0; i < len; i ++) {
        result += resultReverse[len - i - 1];
    }

    return result;
}
#include <iostream>

#include "bigint.hh"

using namespace extypes;
using namespace std;

int main() {
    bigint a = 999999999999, b = 998;
    cout << a / b << endl;
    return 0;
}

#include <iostream>

#include "bigint.hh"

using namespace extypes;
using namespace std;

int main() {
    long long an = 9111111111;
    long long bn = 9111111111;
    bigint a(an);
    bigint b(bn);
    // cout << a.multiplication(b) << endl;
    a /= b;
    cout << a << endl;

    return 0;
}

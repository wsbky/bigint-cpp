#include "bigint.hh"

#include <cmath>
#include <sstream>

namespace extypes {

bigint::bigint() : pos(true) {}
bigint::bigint(int n) : pos(n >= 0) {
    n = std::abs(n);
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(unsigned n) : pos(true) {
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(long n) : pos(n >= 0) {
    n = std::abs(n);
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(unsigned long n) : pos(true) {
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}

}  // namespace extypes

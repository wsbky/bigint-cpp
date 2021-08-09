#pragma once

#include <vector>

namespace extypes {
struct bigint {
    bigint();
    bigint(int);
    bigint(unsigned);
    bigint(long);
    bigint(unsigned long);

  private:
    std::vector<unsigned> num;
    bool pos;
    const static unsigned base = 1000000000;
};
}  // namespace extypes

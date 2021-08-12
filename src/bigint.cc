#include "bigint.hh"

namespace extypes {

bigint::bigint() : pos(true) {}
bigint::bigint(int n) : pos(n >= 0) {
    n = std::abs(n);
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(unsigned n, bool p = true) : pos(p) {
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
bigint::bigint(unsigned long n, bool p = true) : pos(p) {
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(long long n) : pos(n >= 0) {
    n = std::abs(n);
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(std::vector<unsigned> a, bool p = true) : num(a), pos(p) {}
bigint::bigint(const bigint &a) : num(a.num), pos(a.pos) {}

bool bigint::sign() const { return pos; }
bigint bigint::abs() const { return bigint(num, true); }
// TODO: fact
// TODO: digits

// TODO: input & output
std::string bigint::to_string() const {
    std::ostringstream ros;
    if (num.size() == 0) return "NaN";
    if (!pos) ros << "-";
    ros << num.at(num.size() - 1);
    if (num.size() >= 1)
        std::for_each(num.rbegin() + 1, num.rend(), [&](const auto &e) {
            ros << std::setfill('0') << std::setw(base_len - 1) << e;
        });
    return ros.str();
}
std::ostream &operator<<(std::ostream &os, const bigint &a) {
    return os << a.to_string();
}

// TODO: casting operators

bigint bigint::operator+() const { return *this; }
bigint bigint::operator-() const { return bigint(num, !pos); }

unsigned bigint::operator[](int a) const { return num.at(a); }

bigint &bigint::operator+=(const bigint &a) {
    if (pos ^ a.pos) return *this -= -a;

    bigint t(a);
    unsigned moveup = 0;
    if (num.size() < a.num.size()) {
        t = *this;
        *this = a;
        t.num.resize(num.size(), 0);
    }

    auto it_t = t.num.begin();
    for (auto &e : num) {
        e += (*it_t++) + moveup;
        moveup = (e >= base) ? 1 : 0;
        e -= base;
    }
    if (moveup) num.push_back(moveup);
    return *this;
}
bigint &bigint::operator+=(int a) { return *this += bigint(a); }
bigint &bigint::operator+=(unsigned a) { return *this += bigint(a); }
bigint &bigint::operator+=(long a) { return *this += bigint(a); }
bigint &bigint::operator+=(unsigned long a) { return *this += bigint(a); }

bigint &bigint::operator-=(const bigint &a) {
    if (pos ^ a.pos) return *this += -a;

    bigint t(a);
    unsigned moveup = 0;
    bool rev_flag = false;
    if ((*this).abs() < a.abs()) {
        rev_flag = true;
        t = *this;
        *this = a;
        if (num.size() > t.num.size()) t.num.resize(num.size(), 0);
    }

    auto it_t = t.num.begin();
    for (auto &e : num) {
        e += base - (*it_t++) + moveup;
        if (e >= base) {
            e -= base;
            moveup = 0;
        } else
            moveup = -1;
    }
    if (num.at(num.size() - 1) == 0) num.pop_back();

    if (rev_flag ^ pos) pos = !pos;
    return *this;
}
bigint &bigint::operator-=(int a) { return *this -= bigint(a); }
bigint &bigint::operator-=(unsigned a) { return *this -= bigint(a); }
bigint &bigint::operator-=(long a) { return *this -= bigint(a); }
bigint &bigint::operator-=(unsigned long a) { return *this -= bigint(a); }

bigint &bigint::operator*=(const bigint &a) {
    return (*this).multiplication_a(a);
}
bigint &bigint::operator*=(int a) { return *this *= bigint(a); }
bigint &bigint::operator*=(unsigned a) { return *this *= bigint(a); }
bigint &bigint::operator*=(long a) { return *this *= bigint(a); }
bigint &bigint::operator*=(unsigned long a) { return *this *= bigint(a); }

bigint &bigint::operator/=(const bigint &a) { return (*this).division_a(a); }
bigint &bigint::operator/=(int a) { return *this /= bigint(a); }
bigint &bigint::operator/=(unsigned a) { return *this /= bigint(a); }
bigint &bigint::operator/=(long a) { return *this /= bigint(a); }
bigint &bigint::operator/=(unsigned long a) { return *this /= bigint(a); }

bigint bigint::operator*(const bigint &a) const {
    bigint t(*this);
    return (t *= a);
}
bigint bigint::operator*(int a) const {
    bigint t(*this);
    return (t *= a);
}
bigint bigint::operator*(unsigned a) const {
    bigint t(*this);
    return (t *= a);
}
bigint bigint::operator*(long a) const {
    bigint t(*this);
    return (t *= a);
}
bigint bigint::operator*(unsigned long a) const {
    bigint t(*this);
    return (t *= a);
}

bigint &bigint::operator=(const bigint &a) {
    num = a.num;
    pos = a.pos;
    return *this;
}

bool bigint::operator==(const bigint &a) const {
    return (pos == a.pos) && (num.size() == a.num.size()) &&
           std::equal(num.cbegin(), num.cend(), a.num.cbegin());
}
bool bigint::operator==(int a) const { return *this == bigint(a); }
bool bigint::operator==(unsigned a) const { return *this == bigint(a); }
bool bigint::operator==(long a) const { return *this == bigint(a); }
bool bigint::operator==(unsigned long a) const { return *this == bigint(a); }

bool bigint::operator>(const bigint &a) const {
    if (pos ^ a.pos) {
        if (pos) return true;
        else
            return false;
    }
    if (num.size() > a.num.size()) return true;
    if (num.size() < a.num.size()) return false;
    for (int i = num.size() - 1; i >= 0; --i) {
        if (num.at(i) > a.num.at(i)) return true;
        if (num.at(i) < a.num.at(i)) return false;
    }
    return false;
}
bool bigint::operator>(int a) const { return *this > bigint(a); }
bool bigint::operator>(unsigned a) const { return *this > bigint(a); }
bool bigint::operator>(long a) const { return *this > bigint(a); }
bool bigint::operator>(unsigned long a) const { return *this > bigint(a); }
bool operator>(int a, const bigint &b) { return b < bigint(a); }
bool operator>(unsigned a, const bigint &b) { return b < bigint(a); }
bool operator>(long a, const bigint &b) { return b < bigint(a); }
bool operator>(unsigned long a, const bigint &b) { return b < bigint(a); }

bool bigint::operator>=(const bigint &a) const { return !(*this < a); }
bool bigint::operator>=(int a) const { return *this >= bigint(a); }
bool bigint::operator>=(unsigned a) const { return *this >= bigint(a); }
bool bigint::operator>=(long a) const { return *this >= bigint(a); }
bool bigint::operator>=(unsigned long a) const { return *this >= bigint(a); }
bool operator>=(int a, const bigint &b) { return b <= bigint(a); }
bool operator>=(unsigned a, const bigint &b) { return b <= bigint(a); }
bool operator>=(long a, const bigint &b) { return b <= bigint(a); }
bool operator>=(unsigned long a, const bigint &b) { return b <= bigint(a); }

bool bigint::operator<(const bigint &a) const {
    if (pos ^ a.pos) {
        if (pos) return false;
        else
            return true;
    }
    if (num.size() > a.num.size()) return false;
    if (num.size() < a.num.size()) return true;
    for (auto i = num.size() - 1;; --i) {
        if (num.at(i) > a.num.at(i)) return false;
        if (num.at(i) < a.num.at(i)) return true;
        if (i == 0) break;
    }
    return false;
}
bool bigint::operator<(int a) const { return *this < bigint(a); }
bool bigint::operator<(unsigned a) const { return *this < bigint(a); }
bool bigint::operator<(long a) const { return *this < bigint(a); }
bool bigint::operator<(unsigned long a) const { return *this < bigint(a); }
bool operator<(int a, const bigint &b) { return b > bigint(a); }
bool operator<(unsigned a, const bigint &b) { return b > bigint(a); }
bool operator<(long a, const bigint &b) { return b > bigint(a); }
bool operator<(unsigned long a, const bigint &b) { return b > bigint(a); }

bool bigint::operator<=(const bigint &a) const { return !(*this > a); }
bool bigint::operator<=(int a) const { return *this <= bigint(a); }
bool bigint::operator<=(unsigned a) const { return *this <= bigint(a); }
bool bigint::operator<=(long a) const { return *this <= bigint(a); }
bool bigint::operator<=(unsigned long a) const { return *this <= bigint(a); }
bool operator<=(int a, const bigint &b) { return b >= bigint(a); }
bool operator<=(unsigned a, const bigint &b) { return b >= bigint(a); }
bool operator<=(long a, const bigint &b) { return b >= bigint(a); }
bool operator<=(unsigned long a, const bigint &b) { return b >= bigint(a); }

}  // namespace extypes

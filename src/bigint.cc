// MIT License
//
// Copyright (c) 2021 wsbky
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "bigint.hh"

namespace extypes {

bigint::bigint() : pos(true) {}
bigint::bigint(int n) : pos(n >= 0) {
    n = std::abs(n);
    if (n == 0) num.push_back(0);
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(unsigned n, bool p) : pos(p) {
    if (n == 0) num.push_back(0);
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(long n) : pos(n >= 0) {
    n = std::abs(n);
    if (n == 0) num.push_back(0);
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(unsigned long n, bool p) : pos(p) {
    if (n == 0) num.push_back(0);
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(long long n) : pos(n >= 0) {
    n = std::abs(n);
    if (n == 0) num.push_back(0);
    while (n != 0) {
        num.push_back(n % base);
        n /= base;
    }
}
bigint::bigint(std::vector<unsigned> a, bool p) : num(a), pos(p) {}
bigint::bigint(std::string a) {
    pos = true;
    if (a.length() == 0) return;

    if (a.at(0) == '+' || a.at(0) == '-') {
        pos = (a.at(0) == '+');
        a.erase(a.begin());
    }
    if (!std::all_of(a.begin(), a.end(), isdigit))
        throw std::invalid_argument("Invalid argument.");

    std::vector<std::string> t;

    auto oa_len = a.length();
    for (unsigned long i = 0; i < oa_len / (base_len - 1); ++i) {
        t.push_back(a.substr(a.length() - base_len + 1));
        a.erase(a.end() - base_len + 1, a.end());
    }
    std::for_each(t.begin(), t.end(),
                  [&](const auto &e) { num.push_back(std::stoi(e)); });
    if (a.length() % (base_len - 1) != 0) num.push_back(std::stoi(a));
}
bigint::bigint(const bigint &a) : num(a.num), pos(a.pos) {}

bool bigint::sign() const { return pos; }
bigint bigint::abs() const { return bigint(num, true); }
bigint bigint::fact() const {
    bigint r = 1;
    for (bigint i = 1; i <= *this; ++i) {
        r *= i;
    }
    return r;
}
std::string::size_type bigint::digits() const {
    return (*this).to_string().length() - (pos ? 0 : 1);
}

std::string bigint::to_string() const {
    std::ostringstream ros;
    if (num.size() == 0) return "NaN";
    if (!pos && !(num.size() == 1 && num.at(0) == 0)) ros << "-";
    ros << num.at(num.size() - 1);
    if (num.size() >= 2)
        std::for_each(num.rbegin() + 1, num.rend(), [&](const auto &e) {
            ros << std::setfill('0') << std::setw(base_len - 1) << e;
        });
    return ros.str();
}
std::ostream &operator<<(std::ostream &os, const bigint &a) {
    return os << a.to_string();
}
std::istream &operator>>(std::istream &is, bigint &a) {
    std::string b;
    is >> b;
    a = b;
    return is;
}

bigint::operator int() const {
    if (*this > INT_MAX || *this < INT_MIN)
        throw std::out_of_range("Object is out of the range of Int.");
    int r = 0;
    std::for_each(num.begin(), num.end(), [&](const auto &e) { r -= e; });
    if (pos) r *= -1;
    return r;
}
bigint::operator unsigned() const {
    if (*this > UINT_MAX || !pos)
        throw std::out_of_range("Object is out of the range of Unsigned Int.");
    unsigned r = 0;
    std::for_each(num.begin(), num.end(), [&](const auto &e) { r += e; });
    return r;
}
bigint::operator long() const {
    if (*this > LONG_MAX || *this < LONG_MIN)
        throw std::out_of_range("Object is out of the range of Long.");
    long r = 0;
    std::for_each(num.begin(), num.end(), [&](const auto &e) { r -= e; });
    if (pos) r *= -1;
    return r;
}
bigint::operator unsigned long() const {
    if (*this > ULONG_MAX || !pos)
        throw std::out_of_range("Object is out of the range of Unsigned Long.");
    unsigned long r = 0;
    std::for_each(num.begin(), num.end(), [&](const auto &e) { r += e; });
    return r;
}

bigint bigint::operator+() const { return *this; }
bigint bigint::operator-() const { return bigint(num, !pos); }

bigint &bigint::operator++() { return *this += 1; }
bigint bigint::operator++(int) {
    bigint t(*this);
    t += 1;
    return t;
}
bigint &bigint::operator--() { return *this -= 1; }
bigint bigint::operator--(int) {
    bigint t(*this);
    t -= 1;
    return t;
}

unsigned bigint::operator[](int a) const { return num.at(a); }

bigint &bigint::operator+=(const bigint &a) {
    if (num.empty() || a.num.empty()) {
        throw std::runtime_error("Operator+=: Object is empty.");
    }

    if (pos ^ a.pos) return *this -= -a;

    bigint t(a);
    short moveup = 0;
    if (num.size() < a.num.size()) {
        t = *this;
        *this = a;
        t.num.resize(num.size(), 0);
    }

    auto it_t = t.num.begin();
    for (auto &e : num) {
        e += (*it_t++) + moveup;
        moveup = (e >= base) ? 1 : 0;
        if (moveup) e -= base;
    }
    if (moveup) num.push_back(moveup);
    return *this;
}
bigint &bigint::operator+=(int a) { return *this += bigint(a); }
bigint &bigint::operator+=(unsigned a) { return *this += bigint(a); }
bigint &bigint::operator+=(long a) { return *this += bigint(a); }
bigint &bigint::operator+=(unsigned long a) { return *this += bigint(a); }
bigint &bigint::operator+=(long long a) { return *this += bigint(a); }

bigint &bigint::operator-=(const bigint &a) {
    if (num.empty() || a.num.empty()) {
        throw std::runtime_error("Operator-=: Object is empty.");
    }

    if (pos ^ a.pos) return *this += -a;

    bigint t(a);
    short moveup = 0;
    bool rev_flag = false;
    if ((*this).abs() < a.abs()) {
        rev_flag = true;
        t = *this;
        *this = a;
    }
    if (num.size() > t.num.size()) t.num.resize(num.size(), 0);

    auto it_t = t.num.begin();
    for (auto &e : num) {
        e += base - (*it_t++) + moveup;
        if (e >= base) {
            e -= base;
            moveup = 0;
        } else
            moveup = -1;
    }
    if (num.at(num.size() - 1) == 0 && num.size() != 1) num.pop_back();

    pos ^= rev_flag;
    return *this;
}
bigint &bigint::operator-=(int a) { return *this -= bigint(a); }
bigint &bigint::operator-=(unsigned a) { return *this -= bigint(a); }
bigint &bigint::operator-=(long a) { return *this -= bigint(a); }
bigint &bigint::operator-=(unsigned long a) { return *this -= bigint(a); }
bigint &bigint::operator-=(long long a) { return *this -= bigint(a); }

bigint &bigint::operator*=(const bigint &a) {
    return (*this).multiplication_a(a);
}
bigint &bigint::operator*=(int a) { return *this *= bigint(a); }
bigint &bigint::operator*=(unsigned a) { return *this *= bigint(a); }
bigint &bigint::operator*=(long a) { return *this *= bigint(a); }
bigint &bigint::operator*=(unsigned long a) { return *this *= bigint(a); }
bigint &bigint::operator*=(long long a) { return *this *= bigint(a); }

bigint &bigint::operator/=(const bigint &a) { return (*this).division_a(a); }
bigint &bigint::operator/=(int a) { return *this /= bigint(a); }
bigint &bigint::operator/=(unsigned a) { return *this /= bigint(a); }
bigint &bigint::operator/=(long a) { return *this /= bigint(a); }
bigint &bigint::operator/=(unsigned long a) { return *this /= bigint(a); }
bigint &bigint::operator/=(long long a) { return *this *= bigint(a); }

bigint &bigint::operator%=(const bigint &a) { return *this -= a * (*this / a); }
bigint &bigint::operator%=(int a) { return *this %= bigint(a); }
bigint &bigint::operator%=(unsigned a) { return *this %= bigint(a); }
bigint &bigint::operator%=(long a) { return *this %= bigint(a); }
bigint &bigint::operator%=(unsigned long a) { return *this %= bigint(a); }
bigint &bigint::operator%=(long long a) { return *this %= bigint(a); }

bigint bigint::operator+(const bigint &a) const {
    bigint t(*this);
    return t += a;
}
bigint bigint::operator+(int a) const {
    bigint t(*this);
    return t += a;
}
bigint bigint::operator+(unsigned a) const {
    bigint t(*this);
    return t += a;
}
bigint bigint::operator+(long a) const {
    bigint t(*this);
    return t += a;
}
bigint bigint::operator+(unsigned long a) const {
    bigint t(*this);
    return t += a;
}
bigint bigint::operator+(long long a) const {
    bigint t(*this);
    return t += a;
}
bigint operator+(int a, const bigint &b) { return bigint(a) + b; }
bigint operator+(unsigned a, const bigint &b) { return bigint(a) + b; }
bigint operator+(long a, const bigint &b) { return bigint(a) + b; }
bigint operator+(unsigned long a, const bigint &b) { return bigint(a) + b; }
bigint operator+(long long a, const bigint &b) { return bigint(a) + b; }

bigint bigint::operator-(const bigint &a) const {
    bigint t(*this);
    return t -= a;
}
bigint bigint::operator-(int a) const {
    bigint t(*this);
    return t -= a;
}
bigint bigint::operator-(unsigned a) const {
    bigint t(*this);
    return t -= a;
}
bigint bigint::operator-(long a) const {
    bigint t(*this);
    return t -= a;
}
bigint bigint::operator-(unsigned long a) const {
    bigint t(*this);
    return t -= a;
}
bigint bigint::operator-(long long a) const {
    bigint t(*this);
    return t -= a;
}
bigint operator-(int a, const bigint &b) { return bigint(a) - b; }
bigint operator-(unsigned a, const bigint &b) { return bigint(a) - b; }
bigint operator-(long a, const bigint &b) { return bigint(a) - b; }
bigint operator-(unsigned long a, const bigint &b) { return bigint(a) - b; }
bigint operator-(long long a, const bigint &b) { return bigint(a) - b; }

bigint bigint::operator*(const bigint &a) const {
    bigint t(*this);
    return t *= a;
}
bigint bigint::operator*(int a) const {
    bigint t(*this);
    return t *= a;
}
bigint bigint::operator*(unsigned a) const {
    bigint t(*this);
    return t *= a;
}
bigint bigint::operator*(long a) const {
    bigint t(*this);
    return t *= a;
}
bigint bigint::operator*(unsigned long a) const {
    bigint t(*this);
    return t *= a;
}
bigint bigint::operator*(long long a) const {
    bigint t(*this);
    return t *= a;
}
bigint operator*(int a, const bigint &b) { return bigint(a) * b; }
bigint operator*(unsigned a, const bigint &b) { return bigint(a) * b; }
bigint operator*(long a, const bigint &b) { return bigint(a) * b; }
bigint operator*(unsigned long a, const bigint &b) { return bigint(a) * b; }
bigint operator*(long long a, const bigint &b) { return bigint(a) * b; }

bigint bigint::operator/(const bigint &a) const {
    bigint t(*this);
    return t /= a;
}
bigint bigint::operator/(int a) const {
    bigint t(*this);
    return t /= a;
}
bigint bigint::operator/(unsigned a) const {
    bigint t(*this);
    return t /= a;
}
bigint bigint::operator/(long a) const {
    bigint t(*this);
    return t /= a;
}
bigint bigint::operator/(unsigned long a) const {
    bigint t(*this);
    return t /= a;
}
bigint bigint::operator/(long long a) const {
    bigint t(*this);
    return t /= a;
}
bigint operator/(int a, const bigint &b) { return bigint(a) / b; }
bigint operator/(unsigned a, const bigint &b) { return bigint(a) / b; }
bigint operator/(long a, const bigint &b) { return bigint(a) / b; }
bigint operator/(unsigned long a, const bigint &b) { return bigint(a) / b; }
bigint operator/(long long a, const bigint &b) { return bigint(a) / b; }

bigint bigint::operator%(const bigint &a) const {
    bigint t(*this);
    return t %= a;
}
bigint bigint::operator%(int a) const {
    bigint t(*this);
    return t %= a;
}
bigint bigint::operator%(unsigned a) const {
    bigint t(*this);
    return t %= a;
}
bigint bigint::operator%(long a) const {
    bigint t(*this);
    return t %= a;
}
bigint bigint::operator%(unsigned long a) const {
    bigint t(*this);
    return t %= a;
}
bigint bigint::operator%(long long a) const {
    bigint t(*this);
    return t %= a;
}
bigint operator%(int a, const bigint &b) { return bigint(a) % b; }
bigint operator%(unsigned a, const bigint &b) { return bigint(a) % b; }
bigint operator%(long a, const bigint &b) { return bigint(a) % b; }
bigint operator%(unsigned long a, const bigint &b) { return bigint(a) % b; }
bigint operator%(long long a, const bigint &b) { return bigint(a) % b; }

bigint &bigint::operator=(const bigint &a) {
    num = a.num;
    pos = a.pos;
    return *this;
}
bigint &bigint::operator=(int a) { return *this = bigint(a); }
bigint &bigint::operator=(unsigned a) { return *this = bigint(a); }
bigint &bigint::operator=(long a) { return *this = bigint(a); }
bigint &bigint::operator=(unsigned long a) { return *this = bigint(a); }
bigint &bigint::operator=(long long a) { return *this = bigint(a); }
bigint &bigint::operator=(std::string a) { return *this = bigint(a); }

bool bigint::operator==(const bigint &a) const {
    if (num.at(0) == 0 && a.num.at(0) == 0 && num.size() == 1 &&
        a.num.size() == 1)
        return true;
    return (pos == a.pos) && (num.size() == a.num.size()) &&
           std::equal(num.cbegin(), num.cend(), a.num.cbegin());
}
bool bigint::operator==(int a) const { return *this == bigint(a); }
bool bigint::operator==(unsigned a) const { return *this == bigint(a); }
bool bigint::operator==(long a) const { return *this == bigint(a); }
bool bigint::operator==(unsigned long a) const { return *this == bigint(a); }
bool bigint::operator==(long long a) const { return *this == bigint(a); }

bool bigint::operator>(const bigint &a) const {
    if (pos ^ a.pos) {
        if (pos) return true;
        else
            return false;
    }
    if (num.size() > a.num.size()) return true;
    if (num.size() < a.num.size()) return false;
    for (auto i = num.size() - 1;; --i) {
        if (num.at(i) > a.num.at(i)) return true;
        if (num.at(i) < a.num.at(i)) return false;
        if (i == 0) break;
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
bool operator>(long long a, const bigint &b) { return b < bigint(a); }

bool bigint::operator>=(const bigint &a) const { return !(*this < a); }
bool bigint::operator>=(int a) const { return *this >= bigint(a); }
bool bigint::operator>=(unsigned a) const { return *this >= bigint(a); }
bool bigint::operator>=(long a) const { return *this >= bigint(a); }
bool bigint::operator>=(unsigned long a) const { return *this >= bigint(a); }
bool operator>=(int a, const bigint &b) { return b <= bigint(a); }
bool operator>=(unsigned a, const bigint &b) { return b <= bigint(a); }
bool operator>=(long a, const bigint &b) { return b <= bigint(a); }
bool operator>=(unsigned long a, const bigint &b) { return b <= bigint(a); }
bool operator>=(long long a, const bigint &b) { return b <= bigint(a); }

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
bool operator<(long long a, const bigint &b) { return b > bigint(a); }

bool bigint::operator<=(const bigint &a) const { return !(*this > a); }
bool bigint::operator<=(int a) const { return *this <= bigint(a); }
bool bigint::operator<=(unsigned a) const { return *this <= bigint(a); }
bool bigint::operator<=(long a) const { return *this <= bigint(a); }
bool bigint::operator<=(unsigned long a) const { return *this <= bigint(a); }
bool operator<=(int a, const bigint &b) { return b >= bigint(a); }
bool operator<=(unsigned a, const bigint &b) { return b >= bigint(a); }
bool operator<=(long a, const bigint &b) { return b >= bigint(a); }
bool operator<=(unsigned long a, const bigint &b) { return b >= bigint(a); }
bool operator<=(long long a, const bigint &b) { return b >= bigint(a); }

bigint pow(const bigint &a, int b) {
    bigint r = 1;
    for (int i = 0; i < b; ++i) {
        r *= a;
    }
    return r;
}
bigint abs(const bigint &a) { return a.abs(); }

}  // namespace extypes

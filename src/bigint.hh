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

#pragma once

#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace extypes {
struct bigint {
    bigint();
    bigint(int);
    bigint(unsigned, bool p = true);
    bigint(long);
    bigint(unsigned long, bool p = true);
    bigint(long long);
    bigint(std::vector<unsigned>, bool p = true);
    bigint(std::string);
    bigint(const bigint &);

    bool sign() const;
    bigint abs() const;
    bigint fact() const;
    std::string::size_type digits() const;

    std::string to_string() const;
    friend std::ostream &operator<<(std::ostream &, const bigint &);
    friend std::istream &operator>>(std::istream &, bigint &);

    operator int() const;
    operator unsigned() const;
    operator long() const;
    operator unsigned long() const;

    bigint operator+() const;
    bigint operator-() const;

    bigint &operator++();
    bigint operator++(int);
    bigint &operator--();
    bigint operator--(int);

    unsigned operator[](int) const;

    bigint &operator+=(const bigint &);
    bigint &operator+=(int);
    bigint &operator+=(unsigned);
    bigint &operator+=(long);
    bigint &operator+=(unsigned long);
    bigint &operator+=(long long);

    bigint &operator-=(const bigint &);
    bigint &operator-=(int);
    bigint &operator-=(unsigned);
    bigint &operator-=(long);
    bigint &operator-=(unsigned long);
    bigint &operator-=(long long);

    bigint &operator*=(const bigint &);
    bigint &operator*=(int);
    bigint &operator*=(unsigned);
    bigint &operator*=(long);
    bigint &operator*=(unsigned long);
    bigint &operator*=(long long);

    bigint &operator/=(const bigint &);
    bigint &operator/=(int);
    bigint &operator/=(unsigned);
    bigint &operator/=(long);
    bigint &operator/=(unsigned long);
    bigint &operator/=(long long);

    bigint &operator%=(const bigint &);
    bigint &operator%=(int);
    bigint &operator%=(unsigned);
    bigint &operator%=(long);
    bigint &operator%=(unsigned long);
    bigint &operator%=(long long);

    bigint operator+(const bigint &) const;
    bigint operator+(int) const;
    bigint operator+(unsigned) const;
    bigint operator+(long) const;
    bigint operator+(unsigned long) const;
    bigint operator+(long long) const;
    friend bigint operator+(int, const bigint &);
    friend bigint operator+(unsigned, const bigint &);
    friend bigint operator+(long, const bigint &);
    friend bigint operator+(unsigned long, const bigint &);
    friend bigint operator+(long long, const bigint &);

    bigint operator-(const bigint &) const;
    bigint operator-(int) const;
    bigint operator-(unsigned) const;
    bigint operator-(long) const;
    bigint operator-(unsigned long) const;
    bigint operator-(long long) const;
    friend bigint operator-(int, const bigint &);
    friend bigint operator-(unsigned, const bigint &);
    friend bigint operator-(long, const bigint &);
    friend bigint operator-(unsigned long, const bigint &);
    friend bigint operator-(long long, const bigint &);

    bigint operator*(const bigint &) const;
    bigint operator*(int) const;
    bigint operator*(unsigned) const;
    bigint operator*(long) const;
    bigint operator*(unsigned long) const;
    bigint operator*(long long) const;
    friend bigint operator*(int, const bigint &);
    friend bigint operator*(unsigned, const bigint &);
    friend bigint operator*(long, const bigint &);
    friend bigint operator*(unsigned long, const bigint &);
    friend bigint operator*(long long, const bigint &);

    bigint operator/(const bigint &) const;
    bigint operator/(int) const;
    bigint operator/(unsigned) const;
    bigint operator/(long) const;
    bigint operator/(unsigned long) const;
    bigint operator/(long long) const;
    friend bigint operator/(int, const bigint &);
    friend bigint operator/(unsigned, const bigint &);
    friend bigint operator/(long, const bigint &);
    friend bigint operator/(unsigned long, const bigint &);
    friend bigint operator/(long long, const bigint &);

    bigint operator%(const bigint &) const;
    bigint operator%(int) const;
    bigint operator%(unsigned) const;
    bigint operator%(long) const;
    bigint operator%(unsigned long) const;
    bigint operator%(long long) const;
    friend bigint operator%(int, const bigint &);
    friend bigint operator%(unsigned, const bigint &);
    friend bigint operator%(long, const bigint &);
    friend bigint operator%(unsigned long, const bigint &);
    friend bigint operator%(long long, const bigint &);

    bigint &operator=(const bigint &);
    bigint &operator=(int);
    bigint &operator=(unsigned);
    bigint &operator=(long);
    bigint &operator=(unsigned long);
    bigint &operator=(long long);
    bigint &operator=(std::string);

    bool operator==(const bigint &) const;
    bool operator==(int) const;
    bool operator==(unsigned) const;
    bool operator==(long) const;
    bool operator==(unsigned long) const;
    bool operator==(long long) const;

    bool operator>(const bigint &) const;
    bool operator>(int) const;
    bool operator>(unsigned) const;
    bool operator>(long) const;
    bool operator>(unsigned long) const;
    bool operator>(long long) const;
    friend bool operator>(int, const bigint &);
    friend bool operator>(unsigned, const bigint &);
    friend bool operator>(long, const bigint &);
    friend bool operator>(unsigned long, const bigint &);
    friend bool operator>(long long, const bigint &);

    bool operator>=(const bigint &) const;
    bool operator>=(int) const;
    bool operator>=(unsigned) const;
    bool operator>=(long) const;
    bool operator>=(unsigned long) const;
    bool operator>=(long long) const;
    friend bool operator>=(int, const bigint &);
    friend bool operator>=(unsigned, const bigint &);
    friend bool operator>=(long, const bigint &);
    friend bool operator>=(unsigned long, const bigint &);
    friend bool operator>=(long long, const bigint &);

    bool operator<(const bigint &) const;
    bool operator<(int) const;
    bool operator<(unsigned) const;
    bool operator<(long) const;
    bool operator<(unsigned long) const;
    bool operator<(long long) const;
    friend bool operator<(int, const bigint &);
    friend bool operator<(unsigned, const bigint &);
    friend bool operator<(long, const bigint &);
    friend bool operator<(unsigned long, const bigint &);
    friend bool operator<(long long, const bigint &);

    bool operator<=(const bigint &) const;
    bool operator<=(int) const;
    bool operator<=(unsigned) const;
    bool operator<=(long) const;
    bool operator<=(unsigned long) const;
    bool operator<=(long long) const;
    friend bool operator<=(int, const bigint &);
    friend bool operator<=(unsigned, const bigint &);
    friend bool operator<=(long, const bigint &);
    friend bool operator<=(unsigned long, const bigint &);
    friend bool operator<=(long long, const bigint &);

    friend bigint pow(const bigint &, int);
    friend bigint abs(const bigint &);

  private:
    std::vector<unsigned> num;
    bool pos;
    const static unsigned base = 1000000000;
    const static unsigned short base_len = 10;

    bigint &multiplication_a(const bigint &a) {
        if (num.empty() || a.num.empty()) {
            throw std::runtime_error("Operator*=: Object is empty.");
        }
        bigint t(*this);
        auto min_dim = t.num.size() + a.num.size() - 2;
        num.clear();
        num.resize(min_dim + 1);
        for (auto it_t = t.num.begin(); it_t != t.num.end(); ++it_t)
            for (auto it_a = a.num.begin(); it_a != a.num.end(); ++it_a) {
                auto dim = (it_a - a.num.begin()) + (it_t - t.num.begin());
                unsigned long long tmp =
                    (unsigned long long)*it_t * (unsigned long long)*it_a;
                for (int i = 0; tmp != 0; ++i) {
                    if (dim + (unsigned long)i < num.size()) {
                        tmp += num.at(dim + i);
                        num.at(dim + i) = tmp % base;
                    } else
                        num.push_back(tmp % base);
                    tmp /= base;
                }
            }
        pos ^= !a.pos;
        return *this;
    }

    bigint &division_a(const bigint &s) {
        bigint t = (*this).abs();
        bigint a = s.abs();
        if (num.empty() || a.num.empty()) {
            throw std::runtime_error("Operator/=: Object is empty.");
        }
        if (a == 0) throw std::runtime_error("Division by zero");
        if (t < a) {
            num.clear();
            num.push_back(0);
            return *this;
        }
        if (t == a) {
            num.clear();
            num.push_back(1);
            pos ^= !s.pos;
            return *this;
        }
        auto div_t = num.size() - a.num.size() + 1;
        pos ^= !s.pos;
        a = a.abs();
        t = t.abs();
        num.clear();
        num.resize(div_t, 0);
        auto ot_size = t.num.size();
        for (auto i = ot_size - 1; i >= ot_size - div_t; --i) {
            if (i >= t.num.size()) {
                num.at(ot_size - i - 1) = 0;
                continue;
            }
            long long tmp = t.num.at(i);
            if (i != ot_size - 1 && i + 1 < t.num.size())
                tmp += (long long)(t.num.at(i + 1)) * base;
            unsigned q = unsigned(tmp / a.num.at(a.num.size() - 1));
            num.at(ot_size - i - 1) = q;
            std::vector<unsigned> bs = {1};
            for (unsigned long j = 0; j < i; ++j) bs.push_back(0);
            std::reverse(bs.begin(), bs.end());
            bigint bbs(bs);
            t -= a * q * bbs;
            if (i == 0) break;
        }
        std::reverse(num.begin(), num.end());
        for (unsigned long i = num.size() - 1; i >= 1; --i) {
            if (num.at(i) == 0) num.pop_back();
            else
                break;
        }
        return *this;
    }
};

bigint factorial(int);
}  // namespace extypes

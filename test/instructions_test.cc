#include <gtest/gtest.h>

#include "bigint.hh"

using namespace extypes;

TEST(operator_compound_addition, pp) {
    bigint a(1);
    EXPECT_EQ(bigint(2), a += bigint(1));
    bigint b(999999999);
    EXPECT_EQ(bigint(1000000000), b += bigint(1));
    bigint c(9999999999);
    EXPECT_EQ(bigint(100009999999998), c += bigint(99999999999999));
}
TEST(operator_compound_addition, pn) {
    bigint a(1);
    EXPECT_EQ(bigint(0), a += bigint(-1));
    bigint b(1000000000);
    EXPECT_EQ(bigint(1), b += bigint(-999999999));
    bigint c(100009999999998);
    EXPECT_EQ(bigint(9999999999), c += bigint(-99999999999999));
}
TEST(operator_compound_addition, np) {
    bigint a(-1);
    EXPECT_EQ(bigint(0), a += bigint(1));
    bigint b(-1000000000);
    EXPECT_EQ(bigint(-1), b += bigint(999999999));
    bigint c(-100009999999998);
    EXPECT_EQ(bigint(-9999999999), c += bigint(99999999999999));
}
TEST(operator_compound_addition, nn) {
    bigint a(-1);
    EXPECT_EQ(bigint(-2), a += bigint(-1));
    bigint b(-1);
    EXPECT_EQ(bigint(-1000000000), b += bigint(-999999999));
    bigint c(-9999999999);
    EXPECT_EQ(bigint(-100009999999998), c += bigint(-99999999999999));
}
TEST(operator_compound_addition, other_types) {
    unsigned a = 1;
    long b = 1;
    unsigned long c = 1;
    long long d = 1;
    bigint o1(999999999);
    bigint o2(999999999);
    bigint o3(999999999);
    bigint o4(999999999);
    EXPECT_EQ(bigint(1000000000), o1 += a);
    EXPECT_EQ(bigint(1000000000), o2 += b);
    EXPECT_EQ(bigint(1000000000), o3 += c);
    EXPECT_EQ(bigint(1000000000), o4 += d);
}

TEST(operator_compound_subtraction, pp) {
    bigint a(1);
    EXPECT_EQ(bigint(0), a -= bigint(1));
    bigint b(1000000000);
    EXPECT_EQ(bigint(999999999), b -= bigint(1));
    bigint c(100009999999998);
    EXPECT_EQ(bigint(9999999999), c -= bigint(99999999999999));
}
TEST(operator_compound_subtraction, pn) {
    bigint a(1);
    EXPECT_EQ(bigint(2), a -= bigint(-1));
    bigint b(1);
    EXPECT_EQ(bigint(1000000000), b -= bigint(-999999999));
    bigint c(9999999999);
    EXPECT_EQ(bigint(100009999999998), c -= bigint(-99999999999999));
}
TEST(operator_compound_subtraction, np) {
    bigint a(-1);
    EXPECT_EQ(bigint(-2), a -= bigint(1));
    bigint b(-1);
    EXPECT_EQ(bigint(-1000000000), b -= bigint(999999999));
    bigint c(-9999999999);
    EXPECT_EQ(bigint(-100009999999998), c -= bigint(99999999999999));
}
TEST(operator_compound_subtraction, nn) {
    bigint a(-1);
    EXPECT_EQ(bigint(0), a -= bigint(-1));
    bigint b(-1000000000);
    EXPECT_EQ(bigint(-1), b -= bigint(-999999999));
    bigint c(-100009999999998);
    EXPECT_EQ(bigint(-9999999999), c -= bigint(-99999999999999));
}
TEST(operator_compound_subtraction, other_types) {
    unsigned a = 1;
    long b = 1;
    unsigned long c = 1;
    long long d = 1;
    bigint o1(1000000000);
    bigint o2(1000000000);
    bigint o3(1000000000);
    bigint o4(1000000000);
    EXPECT_EQ(bigint(999999999), o1 -= a);
    EXPECT_EQ(bigint(999999999), o2 -= b);
    EXPECT_EQ(bigint(999999999), o3 -= c);
    EXPECT_EQ(bigint(999999999), o4 -= d);
}

TEST(operator_compound_multiplication, pp) {
    bigint a(1);
    EXPECT_EQ(bigint(0), a *= bigint(0));
    bigint b(999999999);
    EXPECT_EQ(bigint(999999998000000001), b *= bigint(999999999));
    bigint c(999999999);
    EXPECT_EQ(bigint(1999999998), c *= bigint(2));
}
TEST(operator_compound_multiplication, pn) {
    bigint a(1);
    EXPECT_EQ(bigint(0), a *= bigint(0));
    a = 1;
    EXPECT_EQ(bigint(-1), a *= bigint(-1));
    bigint b(999999999);
    EXPECT_EQ(bigint(-999999998000000001), b *= bigint(-999999999));
    bigint c(999999999);
    EXPECT_EQ(bigint(-1999999998), c *= bigint(-2));
}
TEST(operator_compound_multiplication, np) {
    bigint a(-1);
    EXPECT_EQ(bigint(-1), a *= bigint(1));
    bigint b(-999999999);
    EXPECT_EQ(bigint(-999999998000000001), b *= bigint(999999999));
    bigint c(-999999999);
    EXPECT_EQ(bigint(-1999999998), c *= bigint(2));
}
TEST(operator_compound_multiplication, nn) {
    bigint a(-1);
    EXPECT_EQ(bigint(1), a *= bigint(-1));
    bigint b(-999999999);
    EXPECT_EQ(bigint(999999998000000001), b *= bigint(-999999999));
    bigint c(-999999999);
    EXPECT_EQ(bigint(1999999998), c *= bigint(-2));
}
TEST(operator_compound_multiplication, other_types) {
    unsigned a = 2;
    long b = 2;
    unsigned long c = 2;
    long long d = 2;
    bigint o1(999999999);
    bigint o2(999999999);
    bigint o3(999999999);
    bigint o4(999999999);
    EXPECT_EQ(bigint(1999999998), o1 *= a);
    EXPECT_EQ(bigint(1999999998), o2 *= b);
    EXPECT_EQ(bigint(1999999998), o3 *= c);
    EXPECT_EQ(bigint(1999999998), o4 *= d);
}

TEST(operator_compound_division, pp) {
    bigint a(1);
    EXPECT_ANY_THROW(a /= 0);
    bigint b(1);
    EXPECT_EQ(bigint(1), b /= bigint(1));
    bigint c(999999999999);
    EXPECT_EQ(bigint(1001001001), c /= bigint(999));
    bigint d(9999999999);
    EXPECT_EQ(bigint(999999999), d /= bigint(10));
    bigint e(999999999999);
    EXPECT_EQ(bigint(999999999), e /= bigint(1000));
    bigint f(999999999999);
    EXPECT_EQ(bigint(1002004008), f /= bigint(998));
}

TEST(method_fact, normal) {
    bigint a(10);
    EXPECT_EQ(bigint(3628800), a.fact());
    bigint b(100);
    EXPECT_EQ(bigint("933262154439441526816992388562667004907159682643816214685"
                     "929638952175999932299156089414639761565182862536979208272"
                     "23758251185210916864000000000000000000000000"),
              b.fact());
}

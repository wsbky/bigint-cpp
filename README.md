# Big integer library for C++

[![Build](https://github.com/wsbky/bigint-cpp/actions/workflows/build.yml/badge.svg)](https://github.com/wsbky/bigint-cpp/actions/workflows/build.yml)
[![Test](https://github.com/wsbky/bigint-cpp/actions/workflows/test.yml/badge.svg)](https://github.com/wsbky/bigint-cpp/actions/workflows/test.yml)

This library provides bigint computation features:

- `src/bigint.hh` : header file
- `src/bigint.cc` : implementation file

## Licence

MIT License. See `LICENSE` file for details.

## Class features

### Constructor

```c++
- bigint()
- bigint(int)
- bigint(unsigned, bool p = true)
- bigint(long)
- bigint(unsigned long, bool p = true)
- bigint(long long)
- bigint(std::vector\<unsigned\>, bool p = true)
- bigint(std::string)
- bigint(const bigint &)
```

### Methods

#### `sign() -> bool`

Returns the sign of `*this`.

```c++
extypes::bigint(1).sign();    // true
extypes::bigint(-1).sign();   // false
```

#### `abs() -> extypes::bigint`

Returns the absolute value of `*this`.

```c++
extypes::bigint(1).abs();    // bigint(1)
extypes::bigint(-1).abs();   // bigint(1)
```

#### `fact() -> extypes::bigint`

Returns the factorial of `*this`.

```c++
extypes::bigint(10).fact();    // bigint(3628800)
extypes::bigint(50).fact();    // bigint(30414093201713378043612608166064768844377641568960512000000000000)
```

#### `digits() -> std::string::size_type`

Returns the number of digits of `*this` as a decimal number.

```c++
extypes::bigint(100).digits();       // 3
extypes::bigint(-100).digits();      // 3
extypes::bigint(14205).digits();     // 5
```

### Functions

#### `pow(extypes::bigint, int) -> extypes::bigint`

Returns bigint powered by int.

```c++
pow(bigint(2), 64);     // bigint(18446744073709551616)
```

#### `abs(bigint) -> extypes::bigint`

Non-member functions of member function `extypes::bigint::abs()`.

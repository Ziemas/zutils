/* SPDX-License-Identifier: MIT */
#ifndef BITUTILS_H_
#define BITUTILS_H_

/*
** https://graphics.stanford.edu/~seander/bithacks.html
*/

namespace zutil {

// Sign extend from Bits wide value to T
template <typename T, unsigned Bits>
static constexpr T SignExtend(const T value)
{
    constexpr auto m { 1 << (Bits - 1) };
    auto x { value & ((1U << Bits) - 1) };
    return (x ^ m) - m;
};

// Test if power of two
static constexpr bool IsPow2(const auto i) { return i && !(i & (i - 1)); }

// Round up to the next power of two
static constexpr auto NextPow2(auto v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

}

#endif // BITUTILS_H_

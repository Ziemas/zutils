/* SPDX-License-Identifier: MIT */
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "bitfield.hh"

using namespace zutil;

TEST_CASE("Bitfield get", "[bitfield]")
{
    enum class f {
        f1,
        f2,
        f3
    };

    Bitfield<unsigned,
        Field<f::f1, 3, 0>,
        Field<f::f2, 7, 4>,
        Field<f::f3, 16, 8>>
        bits(0b000011110110);

    REQUIRE(bits.get<f::f1>() == 0b0110);
    REQUIRE(bits.get<f::f2>() == 0b1111);
    REQUIRE(bits.get<f::f3>() == 0);
    REQUIRE(bits.val() == 0b000011110110);
}

TEST_CASE("Bitfield set", "[bitfield]")
{
    enum class f {
        f1,
        f2,
        f3
    };

    Bitfield<unsigned,
        Field<f::f1, 3, 0>,
        Field<f::f2, 7, 4>,
        Field<f::f3, 16, 8>>
        bits;

    bits.set<f::f1>(0b0110);
    bits.set<f::f2>(0b1111);
    bits.set<f::f3>(0);
    REQUIRE(bits.val() == 0b000011110110);
    REQUIRE(bits == 0b000011110110);
}

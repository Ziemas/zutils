/* SPDX-License-Identifier: MIT */
#include "bitutils.hh"
#include <catch2/catch.hpp>

TEST_CASE("Sign extending", "[sext]")
{
    REQUIRE(zutil::SignExtend<int, 4>(8) < 0);
    REQUIRE(zutil::SignExtend<int, 4>(8) == -8);
    REQUIRE(zutil::SignExtend<int, 4>(0xF) == -1);
}

TEST_CASE("Checking power of 2", "[pow2]")
{
    REQUIRE(zutil::IsPow2(0) == false);
    REQUIRE(zutil::IsPow2(1) == true);
    REQUIRE(zutil::IsPow2(2) == true);
    REQUIRE(zutil::IsPow2(3) == false);
    REQUIRE(zutil::IsPow2(8) == true);
    REQUIRE(zutil::IsPow2(16) == true);
    REQUIRE(zutil::IsPow2(512) == true);
}

TEST_CASE("Rounding to power of 2", "[round2]")
{
    REQUIRE(zutil::NextPow2(3) == 4);
    REQUIRE(zutil::NextPow2(6) == 8);
    REQUIRE(zutil::NextPow2(7) == 8);
    REQUIRE(zutil::NextPow2(400) == 512);
}

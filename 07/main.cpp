#define CATCH_CONFIG_MAIN

#include <iostream>
#include "FormatString.h"
#include "../catch/catch.hpp"

TEST_CASE( "test format" ) {

    SECTION( "test call format without formatting" ){
        auto text = format("");
        REQUIRE(text == "");

        text = format("some string");
        REQUIRE(text == "some string");

        int dummy;
        text = format("some string, dummy var", dummy);
        REQUIRE(text == "some string, dummy var");
    }

    SECTION( "test format with arguments" ){
        auto text = format("{0}", 1);
        REQUIRE(text == "1");

        text = format("{0}", "one");
        REQUIRE(text == "one");

        text = format("{            0         }", "one");
        REQUIRE(text == "one");

        double x = 3.14;
        text = format("{0}", x);
        REQUIRE(text == "3.14");

        text = format("{1}+{1} = {0}", 2, "one");
        REQUIRE(text == "one+one = 2");

        text = format("any text before; {1} + {1} = {0}", 2, "one");
        REQUIRE(text == "any text before; one + one = 2");

        text = format("{1}+{1} = {0}; any text after", 2, "one");
        REQUIRE(text == "one+one = 2; any text after");

        text = format("text before; {1} + {1} = {0}; text after", 2, "one");
        REQUIRE(text == "text before; one + one = 2; text after");

        text = format("{0}{1}{2}{3}{4}{5}", 0, 1, 2, 3, 4, 5);
        REQUIRE(text == "012345");

        text = format("{5}, {4}, {3}, {2}, {1}, {0}", "one", "two", "three",
                "four", "five", "six");
        REQUIRE(text == "six, five, four, three, two, one");
    }

    SECTION( "test wrong brackets" ){
        REQUIRE_THROWS_WITH(format("{"), "Error brackets" );
        REQUIRE_THROWS_WITH(format("}"), "Error brackets" );
        REQUIRE_THROWS_WITH(format("{0} {", 0), "Error brackets" );
        REQUIRE_THROWS_WITH(format("{0} }", 0), "Error brackets" );
        REQUIRE_THROWS_WITH(format(" } {0}", 0), "Error brackets" );
        REQUIRE_THROWS_WITH(format("}0{", 0), "Error brackets" );
        REQUIRE_THROWS_WITH(format("{0} {", 0), "Error brackets" );
        REQUIRE_THROWS_WITH(format(" { {0}", 0), "Error brackets" );
        REQUIRE_THROWS_WITH(format("{{0}}", 0), "Error brackets" );
    }

    SECTION( "test wrong argument number" ){
        REQUIRE_THROWS_WITH(format(" {} ", 0), "Error argument number" );
        REQUIRE_THROWS_WITH(format(" { } ", 0), "Error argument number" );
        REQUIRE_THROWS_WITH(format("{10}", 0), "Error argument number" );
        REQUIRE_THROWS_WITH(format("{%0}", 0), "Error argument number" );
        REQUIRE_THROWS_WITH(format("{0abc}", 0), "Error argument number" );
        REQUIRE_THROWS_WITH(format("{abc}", 0), "Error argument number" );
        REQUIRE_THROWS_WITH(format("{ 0 0 }", 0), "Error argument number" );
        REQUIRE_THROWS_WITH(format("{123456789012345678901234567890}", 0),
                "Error argument number" );
    }

}

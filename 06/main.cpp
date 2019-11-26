#define CATCH_CONFIG_MAIN

#include <iostream>
#include "../catch/catch.hpp"
#include "bigint.h"

TEST_CASE( "test BigInt class" ) {

    SECTION( "test serialize to ostream" ){
        BigInt x(1234567890987654321);
        std::stringstream stream;
        stream << x;
        REQUIRE(stream.str() == std::string("1234567890987654321"));

        stream.str("");
        BigInt y(-1234567890987654321);
        stream << y;
        REQUIRE(stream.str() == std::string("-1234567890987654321"));

        stream.str("");
        BigInt z(0);
        stream << z;
        REQUIRE(stream.str() == std::string("0"));
    }

    SECTION( "test comparision operators" ){
        BigInt a(123456789987654321);
        BigInt b(999999999999999999);
        BigInt c = a;
        REQUIRE(a < b);
        REQUIRE(b > a);
        REQUIRE(a <= b);
        REQUIRE(b >= a);
        REQUIRE(a == a);
        REQUIRE(a == c);
        REQUIRE(a != b);

        REQUIRE(!(a > b));
        REQUIRE(!(b < a));
        REQUIRE(!(a >= b));
        REQUIRE(!(b <= a));
        REQUIRE(!(a != a));
        REQUIRE(!(a != c));
        REQUIRE(!(a == b));

        a = -123456789987654321;
        b = 999999999999999999;
        c = a;
        REQUIRE(a < b);
        REQUIRE(b > a);
        REQUIRE(a <= b);
        REQUIRE(b >= a);
        REQUIRE(a == a);
        REQUIRE(a == c);
        REQUIRE(a != b);

        REQUIRE(!(a > b));
        REQUIRE(!(b < a));
        REQUIRE(!(a >= b));
        REQUIRE(!(b <= a));
        REQUIRE(!(a != a));
        REQUIRE(!(a != c));
        REQUIRE(!(a == b));

        a = -999999999999999999;
        b = -123456789987654321;
        c = a;
        REQUIRE(a < b);
        REQUIRE(b > a);
        REQUIRE(a <= b);
        REQUIRE(b >= a);
        REQUIRE(a == a);
        REQUIRE(a == c);
        REQUIRE(a != b);

        REQUIRE(!(a > b));
        REQUIRE(!(b < a));
        REQUIRE(!(a >= b));
        REQUIRE(!(b <= a));
        REQUIRE(!(a != a));
        REQUIRE(!(a != c));
        REQUIRE(!(a == b));

        a = 0;
        b = 999999999999999999;
        c = a;
        REQUIRE(a < b);
        REQUIRE(b > a);
        REQUIRE(a <= b);
        REQUIRE(b >= a);
        REQUIRE(a == a);
        REQUIRE(a == c);
        REQUIRE(a != b);

        REQUIRE(!(a > b));
        REQUIRE(!(b < a));
        REQUIRE(!(a >= b));
        REQUIRE(!(b <= a));
        REQUIRE(!(a != a));
        REQUIRE(!(a != c));
        REQUIRE(!(a == b));

        a = -123456789987654321;
        b = 0;
        c = a;
        REQUIRE(a < b);
        REQUIRE(b > a);
        REQUIRE(a <= b);
        REQUIRE(b >= a);
        REQUIRE(a == a);
        REQUIRE(a == c);
        REQUIRE(a != b);

        REQUIRE(!(a > b));
        REQUIRE(!(b < a));
        REQUIRE(!(a >= b));
        REQUIRE(!(b <= a));
        REQUIRE(!(a != a));
        REQUIRE(!(a != c));
        REQUIRE(!(a == b));

        a = 0;
        b = 0;
        c = a;
        REQUIRE(a == a);
        REQUIRE(a == c);
        REQUIRE(a == b);
        REQUIRE(!(a > b));
        REQUIRE(!(a < b));
        REQUIRE(!(b < a));
        REQUIRE(!(b > a));
        REQUIRE(a >= b);
        REQUIRE(a <= b);
        REQUIRE(b <= a);
        REQUIRE(b >= a);
        REQUIRE(!(a != a));
        REQUIRE(!(a != c));
        REQUIRE(!(a != b));
    }

    SECTION( "test unary minus" ){
        BigInt x(1234567890987654321);
        std::stringstream stream;
        stream << -x;
        REQUIRE(stream.str() == std::string("-1234567890987654321"));

        stream.str("");
        BigInt y = -x;
        stream << y;
        REQUIRE(stream.str() == std::string("-1234567890987654321"));

        stream.str("");
        BigInt z(-1234567890987654321);
        stream << -z;
        REQUIRE(stream.str() == std::string("1234567890987654321"));

        stream.str("");
        y = -z;
        stream << y;
        REQUIRE(stream.str() == std::string("1234567890987654321"));

        stream.str("");
        y = 0;
        stream << -y;
        REQUIRE(stream.str() == std::string("0"));
        stream.str("");

        z = -y;
        stream << z;
        REQUIRE(stream.str() == std::string("0"));
    }

    SECTION( "test addition" ){
        BigInt x(1111111111111111111);
        BigInt y(2222222222222222222);
        std::stringstream stream;
        stream << x + y;
        REQUIRE(stream.str() == std::string("3333333333333333333"));

        stream.str("");
        x = 999999999999999999;
        stream << x + x + x + x + x + x + x + x + x + x;
        REQUIRE(stream.str() == std::string("9999999999999999990")); // больше long long int

        stream.str("");
        stream << x + 1;
        REQUIRE(stream.str() == std::string("1000000000000000000"));

        y = -987654321123456789;
        stream.str("");
        stream << x + y;
        REQUIRE(stream.str() == std::string("12345678876543210"));

        stream.str("");
        stream << y + x;
        REQUIRE(stream.str() == std::string("12345678876543210"));

        x = -123;
        y = -456;
        stream.str("");
        stream << x + y;
        REQUIRE(stream.str() == std::string("-579"));

        x = 123;
        y = -123;
        stream.str("");
        stream << x + y;
        REQUIRE(stream.str() == std::string("0"));

        x = 123;
        y = 0;
        stream.str("");
        stream << x + y;
        REQUIRE(stream.str() == std::string("123"));

        stream.str("");
        stream << y + x;
        REQUIRE(stream.str() == std::string("123"));

        x = -123;
        y = 0;
        stream.str("");
        stream << x + y;
        REQUIRE(stream.str() == std::string("-123"));

        x = 0;
        y = 0;
        stream.str("");
        stream << x + y;
        REQUIRE(stream.str() == std::string("0"));
    }

    SECTION( "test subtraction" ){
        BigInt x(5555555555555555555);
        BigInt y(2222222222222222222);
        std::stringstream stream;
        stream << x - y;
        REQUIRE(stream.str() == std::string("3333333333333333333"));

        stream.str("");
        stream << y - x;
        REQUIRE(stream.str() == std::string("-3333333333333333333"));

        stream.str("");
        stream << x - x;
        REQUIRE(stream.str() == std::string("0"));

        stream.str("");
        stream << 0 - x;
        REQUIRE(stream.str() == std::string("-5555555555555555555"));

        stream.str("");
        stream << x - 0;
        REQUIRE(stream.str() == std::string("5555555555555555555"));

        x = 111;
        y = -222;
        stream.str("");
        stream << x - y;
        REQUIRE(stream.str() == std::string("333"));

        x = -111;
        y = -222;
        stream.str("");
        stream << x - y;
        REQUIRE(stream.str() == std::string("111"));

        x = -111;
        y = 222;
        stream.str("");
        stream << x - y;
        REQUIRE(stream.str() == std::string("-333"));
    }

    SECTION( "test various arithmetic expressions" ){
        std::stringstream stream;

        BigInt a(12);
        BigInt b(34);
        BigInt c(56);
        BigInt d(78);
        BigInt e(90);
        stream << a + b + c + d + e;
        REQUIRE(stream.str() == std::string("270"));

        stream.str("");
        stream << a - b + c - d + e;
        REQUIRE(stream.str() == std::string("46"));

        stream.str("");
        stream << - a + b - c + d + -e;
        REQUIRE(stream.str() == std::string("-46"));

        stream.str("");
        stream << 100 - a + b - c + d + -e;
        REQUIRE(stream.str() == std::string("54"));

        stream.str("");
        stream << - a + b - c + 100 + d - e;
        REQUIRE(stream.str() == std::string("54"));

        stream.str("");
        stream << - a + b - c + d - e + 100;
        REQUIRE(stream.str() == std::string("54"));

        stream.str("");
        stream << a + (b - c) + -(d + e);
        REQUIRE(stream.str() == std::string("-178"));

        stream.str("");
        stream << a - (b + c) - (d - e - 100);
        REQUIRE(stream.str() == std::string("34"));
    }
}

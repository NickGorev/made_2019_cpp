#define CATCH_CONFIG_MAIN

#include <string>
#include <vector>
#include "../catch/catch.hpp"
#include "parser.h"

TEST_CASE( "test Parser" ) {

    SECTION( "test before and after callbacks" ){
        Parser parser;

        std::string startString;
        auto beforeCallback = [&startString](std::string& token) {
            token = "before " + token;
            startString = token;
            return;
        };

        std::string endString;
        auto afterCallback = [&endString](std::string token) {
            endString = token + " after";
            return;
        };

        parser.setBeforeCallback(beforeCallback);
        parser.setAfterCallback(afterCallback);
        parser.parse("123");

        REQUIRE( startString == std::string("before 123") );
        REQUIRE( endString == std::string("before 123 after") );
    }

    SECTION( "test number callback" ) {
        Parser parser;

        std::vector<int> numbers;
        auto numberCallback = [&numbers](std::string token) {
            numbers.push_back(std::stoi(token));
            return;
        };

        parser.setNumberCallback(numberCallback);
        parser.parse(" 0   a 1 \t b \n 2 c 3  ");

        REQUIRE( numbers.size() == 4 );
        REQUIRE( numbers[0] == 0 );
        REQUIRE( numbers[1] == 1 );
        REQUIRE( numbers[2] == 2 );
        REQUIRE( numbers[3] == 3 );
    }

    SECTION( "test string callback" ) {
        Parser parser;

        std::vector<std::string> stringTokens;
        auto stringCallback = [&stringTokens](std::string token) {
            stringTokens.push_back(token);
            return;
        };

        parser.setStringCallback(stringCallback);
        parser.parse("a 123 b 456 \n \t cde 789 pqrst  ");

        REQUIRE( stringTokens.size() == 4 );
        REQUIRE( stringTokens[0] == std::string("a") );
        REQUIRE( stringTokens[1] == std::string("b") );
        REQUIRE( stringTokens[2] == std::string("cde") );
        REQUIRE( stringTokens[3] == std::string("pqrst") );
    }

    SECTION( "test both number and string callbacks" ) {
        Parser parser;

        std::vector<int> numbers;
        auto numberCallback = [&numbers](std::string token) {
            numbers.push_back(std::stoi(token));
            return;
        };

        std::vector<std::string> stringTokens;
        auto stringCallback = [&stringTokens](std::string token) {
            stringTokens.push_back(token);
            return;
        };

        parser.setNumberCallback(numberCallback);
        parser.setStringCallback(stringCallback);
        parser.parse("9 8 z 7 6 y 5 4 x");

        REQUIRE( numbers.size() == 6 );
        REQUIRE( numbers[0] == 9 );
        REQUIRE( numbers[1] == 8 );
        REQUIRE( numbers[2] == 7 );
        REQUIRE( numbers[3] == 6 );
        REQUIRE( numbers[4] == 5 );
        REQUIRE( numbers[5] == 4 );

        REQUIRE( stringTokens.size() == 3 );
        REQUIRE( stringTokens[0] == std::string("z") );
        REQUIRE( stringTokens[1] == std::string("y") );
        REQUIRE( stringTokens[2] == std::string("x") );
    }

    SECTION( "test all four callbacks" ) {

        std::string startString;
        auto beforeCallback = [&startString](std::string& token) {
            token = "before " + token;
            startString = token;
            return;
        };

        std::string endString;
        auto afterCallback = [&endString](std::string token) {
            endString = token + " after";
            return;
        };

        std::vector<int> numbers;
        auto numberCallback = [&numbers](std::string token) {
            numbers.push_back(std::stoi(token));
            return;
        };

        std::vector<std::string> stringTokens;
        auto stringCallback = [&stringTokens](std::string token) {
            stringTokens.push_back(token);
            return;
        };

        Parser parser(beforeCallback, afterCallback, stringCallback, numberCallback);
        parser.parse("1234567890 pqrs");

        REQUIRE( startString == std::string("before 1234567890 pqrs") );
        REQUIRE( endString == std::string("before 1234567890 pqrs after") );

        REQUIRE( numbers.size() == 1 );
        REQUIRE( numbers[0] == 1234567890 );

        REQUIRE( stringTokens.size() == 2 );
        REQUIRE( stringTokens[0] == std::string("before") );
        REQUIRE( stringTokens[1] == std::string("pqrs") );
    }
}

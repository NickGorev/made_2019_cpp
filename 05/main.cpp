#define CATCH_CONFIG_MAIN

#include <sstream>
#include <iostream>
#include <fstream>

#include "../catch/catch.hpp"

#include "serializer.h"
#include "deserializer.h"

struct Data {
        uint64_t a = 0;
        bool b = false;
        uint64_t c = 0;
        uint64_t d = 0;
        bool e = false;

        template<class Serializer>
        Error serialize(Serializer& serializer) {
            return serializer(a, b, c, d, e);
        }
};

TEST_CASE( "test Serializer/Deserializer" ) {
    SECTION( "test serialize to string" ){
        std::stringstream stream;
        Serializer serializer(stream);

        Data x { 1, false, 2, 564, true };

        Error err = serializer.save(x);

        REQUIRE(err == Error::NoError);
        REQUIRE(stream.str() == std::string("1 false 2 564 true"));
    }

    SECTION( "test deserialize from string" ){
        std::stringstream stream("5 true 864 3 false");
        Deserializer deserializer(stream);

        Data x;

        Error err = deserializer.load(x);

        REQUIRE(err == Error::NoError);
        REQUIRE(x.a == 5);
        REQUIRE(x.b == true);
        REQUIRE(x.c == 864);
        REQUIRE(x.d == 3);
        REQUIRE(x.e == false);
    }

    SECTION( "test serialize/deserialize to/from file" ){
        std::ofstream fs("test.txt");
        Serializer serializer(fs);

        Data x { 123, false, 456, 7890, true };

        Error err = serializer.save(x);
        REQUIRE(err == Error::NoError);

        fs.close();

        std::ifstream ifs("test.txt");
        Deserializer deserializer(ifs);

        Data y;

        err = deserializer.load(y);
        ifs.close();

        REQUIRE(err == Error::NoError);
        REQUIRE(x.a == y.a);
        REQUIRE(x.b == y.b);
        REQUIRE(x.c == y.c);
        REQUIRE(x.d == y.d);
        REQUIRE(x.e == y.e);
    }

    SECTION( "test error while serializing" ){
        std::ofstream fs("");
        Serializer serializer(fs);

        Data x { 123, false, 456, 7890, true };

        Error err = serializer.save(x);
        REQUIRE(err == Error::ErrorSerialize);

        fs.close();
    }

    SECTION( "test error while serializing" ){
        std::ofstream fs("");
        Serializer serializer(fs);

        Data x { 123, false, 456, 7890, true };

        Error err = serializer.save(x);
        REQUIRE(err == Error::ErrorSerialize);

        fs.close();
    }

    SECTION( "test error while deserializing" ){
        std::stringstream stream;
        Deserializer deserializer(stream);

        Data x;

        // это корректная строка
        stream.str("5 true 864 3 false");
        Error err = deserializer.load(x);
        REQUIRE(err == Error::NoError);

        // это неправильная строка
        stream.str("1 2 3 4 5");
        err = deserializer.load(x);
        REQUIRE(err == Error::ErrorDeserialize);

        // еще одна неправильная строка
        stream.str("fake data");
        err = deserializer.load(x);
        REQUIRE(err == Error::ErrorDeserialize);
    }
}

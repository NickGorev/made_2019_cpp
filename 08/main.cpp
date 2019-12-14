#define CATCH_CONFIG_MAIN

#include "allocator.hpp"
#include "vector.hpp"
#include "../catch/catch.hpp"

// Вспомогательная структура;
// будет нужна для того, чтобы проверить равенство
// количества вызовов конструктора количеству вызовов деструктора
// при работе с вектором сложных объектов
struct customClass {
    customClass() { constructor_calls++; }
    customClass(int i) : x(i) { constructor_calls++; }
    customClass(const customClass & other) {
        x = other.x;
        constructor_calls++;
    }
    customClass(customClass && other) {
        x = other.x;
        other.x = 0;
        constructor_calls++;
    }

    ~customClass() { destructor_calls++; }

    customClass & operator=(const customClass & copied) = delete;
    customClass & operator=(customClass && moved) = delete;

    static size_t constructor_calls;
    static size_t destructor_calls;

    static void reset_counters() {
        constructor_calls = 0;
        destructor_calls = 0;
    }

    int x = 0;
};

size_t customClass::constructor_calls = 0;
size_t customClass::destructor_calls = 0;


TEST_CASE( "test Vector" ) {

    SECTION( "test operator[]" ){
        Vector<int> v = {1, 2, 3, 4, 5};
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
        REQUIRE(v[3] == 4);
        REQUIRE(v[4] == 5);
        v[0] = 10;
        v[1] = 9;
        v[2] = 8;
        v[3] = 7;
        v[4] = 6;
        REQUIRE(v[0] == 10);
        REQUIRE(v[1] == 9);
        REQUIRE(v[2] == 8);
        REQUIRE(v[3] == 7);
        REQUIRE(v[4] == 6);
        const int x = v[0];
        REQUIRE(x == 10);
        v[1] = x;
        REQUIRE(v[1] == 10);
    }

    SECTION( "test push_back, size" ){
        Vector<int> v = {1, 2, 3};
        REQUIRE(v.size() == 3);
        int x = 10;
        v.push_back(x);
        REQUIRE(v.size() == 4);
        const int y = 20;
        v.push_back(y);
        REQUIRE(v.size() == 5);
        v.push_back(30);
        REQUIRE(v.size() == 6);

        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
        REQUIRE(v[3] == 10);
        REQUIRE(v[4] == 20);
        REQUIRE(v[5] == 30);
    }

    SECTION( "test pop_back, size" ){
        Vector<int> v = {1, 2, 3};
        REQUIRE(v.size() == 3);
        v.pop_back();
        REQUIRE(v.size() == 2);
    }

    SECTION( "test empty, size" ) {
        Vector<int> v;
        REQUIRE(v.empty());
        v.push_back(0);
        REQUIRE(!v.empty());
    }

    SECTION( "test clear, size, capacity" ) {
        Vector<int> v = {1, 2, 3};
        REQUIRE(v.size() == 3);
        REQUIRE(v.capacity() == 3);
        v.clear();
        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 3);
    }

    SECTION( "test begin, end" ) {
        Vector<int> v(5, 0);
        auto x = v.begin();
        *x = 1;
        REQUIRE(*x == 1);
        REQUIRE(v[0] == 1);

        auto y = v.end();
        y--;
        *y = 2;
        REQUIRE(*y == 2);
        REQUIRE(v[4] == 2);

        int index = 0;
        for(auto z = v.begin(); z != v.end(); ++z) {
            *z = index;
            index++;
        }
        index = 0;
        for(auto z = v.begin(); z != v.end(); z++) {
            REQUIRE(*z == index);
            REQUIRE(v[index] == index);
            index++;
        }
    }

    SECTION( "test rbegin, rend" ) {
        Vector<int> v(5, 0);
        auto x = v.rbegin();
        *x = 1;
        auto y = v.rend();
        y--;
        *y = 2;

        REQUIRE(*x == 1);
        REQUIRE(v[4] == 1);

        REQUIRE(*y == 2);
        REQUIRE(v[0] == 2);

        int index = 0;
        for(auto z = v.rbegin(); z != v.rend(); ++z) {
            *z = index;
            index++;
        }
        index = 0;
        for(auto z = v.rbegin(); z != v.rend(); z++) {
            REQUIRE(*z == index);
            REQUIRE(v[4 - index] == index);
            index++;
        }
    }

    SECTION( "test resize" ) {
        Vector<int> v(1, 0);
        REQUIRE(v.size() == 1);
        v.resize(5);
        REQUIRE(v.size() == 5);
        for(auto z = v.rbegin(); z != v.rend(); z++) {
            REQUIRE(*z == 0);
        }
        v.resize(0);
        REQUIRE(v.size() == 0);
        v.resize(10, 5);
        REQUIRE(v.size() == 10);
        for(auto z = v.rbegin(); z != v.rend(); z++) {
            REQUIRE(*z == 5);
        }
    }

    SECTION( "test reserve" ) {
        Vector<int> v = {1, 2, 3};
        REQUIRE(v.size() == 3);
        REQUIRE(v.capacity() == 3);
        v.reserve(10);
        REQUIRE(v.size() == 3);
        REQUIRE(v.capacity() == 10);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
    }

    SECTION( "test calls constructors/destructors of base class" ) {
        {
            Vector<customClass> v = {1, 2, 3, 4, 5};
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        {
            Vector<customClass> v(10, 5);
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v(10);
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v;
            for(size_t i = 0; i < 10; ++i) {
                customClass x(i);
                v.push_back(x);
            }
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v;
            for(size_t i = 0; i < 10; ++i) {
                customClass x(i);
                v.push_back(x);
            }
            for(size_t i = 0; i < 10; ++i) v.pop_back();
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v(10);
            v.reserve(100);
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v(10);
            v.resize(100);
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v(10, 2);
            v.resize(100, 3);
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v(100);
            v.resize(10);
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v(100, 2);
            v.resize(10);
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v(100);
            v.resize(10, 3);
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v(100, 2);
            v.resize(10, 3);
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v(100, 2);
            v.clear();
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);

        customClass::reset_counters();
        {
            Vector<customClass> v(100);
            v.clear();
        }
        REQUIRE(customClass::constructor_calls == customClass::destructor_calls);
    }

}

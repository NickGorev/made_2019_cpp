#define CATCH_CONFIG_MAIN
#include "../catch/catch.hpp"

#include "allocator.h"

TEST_CASE( "test LinearAllocator" ) {

    SECTION( "if maxSize is too large, allocator does't work" ) {
        LinearAllocator allocator(1000000000000);
        REQUIRE( allocator.alloc(1) == nullptr );
    }

    SECTION( "trying to allocate more than initial maxSize" ) {
        LinearAllocator allocator(10);
        REQUIRE( allocator.alloc(100) == nullptr );
        char* variable1 = allocator.alloc(10);
        char* variable2 = allocator.alloc(7);
        REQUIRE( variable1 != nullptr );
        REQUIRE( variable2 == nullptr );
    }

    SECTION( "allocates memory for various variables" ) {
        LinearAllocator allocator(10);
        char* variable1 = allocator.alloc(1);
        int* variable2 = (int*) allocator.alloc(sizeof(int) * 1);
        *variable1 = 'A';
        *variable2 = 123456789;

        REQUIRE( *variable1 == 'A' );
        REQUIRE( *variable2 == 123456789 );

        *variable1 = 'B';
        *variable2 = 987654321;

        REQUIRE( *variable1 == 'B' );
        REQUIRE( *variable2 == 987654321 );
    }

    SECTION( "check LinearAllocator::reset" ) {
        LinearAllocator allocator(10);
        allocator.alloc(10);
        char* variable2 = allocator.alloc(10);
        REQUIRE( variable2 == nullptr );

        allocator.reset();

        char* variable3 = allocator.alloc(10);
        char* variable4 = allocator.alloc(7);
        REQUIRE( variable3 != nullptr );
        REQUIRE( variable4 == nullptr );

        allocator.reset();

        char* variable5 = allocator.alloc(1);
        int* variable6 = (int*) allocator.alloc(sizeof(int) * 1);
        *variable5 = 'C';
        *variable6 = 1357924680;

        REQUIRE( *variable5 == 'C' );
        REQUIRE( *variable6 == 1357924680 );
    }
}

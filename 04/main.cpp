#define CATCH_CONFIG_MAIN

#include "../catch/catch.hpp"
#include "matrix.h"

TEST_CASE( "test Matrix" ) {

    SECTION( "test getRows" ){
        Matrix matrix(5, 3);
        REQUIRE(matrix.getRows() == 5);
    }

    SECTION( "test getColumns" ) {
        Matrix matrix(5, 3);
        REQUIRE(matrix.getColumns() == 3);
    }

    SECTION( "test setting and getting values by indexing" ) {
        Matrix matrix(2, 3);
        matrix[0][0] = 1;
        matrix[0][1] = 2;
        matrix[0][2] = 3;
        matrix[1][0] = 4;
        matrix[1][1] = 5;
        matrix[1][2] = 6;

        REQUIRE(matrix[0][0] == 1);
        REQUIRE(matrix[0][1] == 2);
        REQUIRE(matrix[0][2] == 3);
        REQUIRE(matrix[1][0] == 4);
        REQUIRE(matrix[1][1] == 5);
        REQUIRE(matrix[1][2] == 6);

        size_t nRows = 7;
        size_t nCols = 12;
        Matrix matrix_2(nRows, nCols);
        for(size_t i = 0; i < nRows; ++i) {
            for(size_t j = 0; j < nCols; ++j) {
                matrix_2[i][j] = (i + 1) * (j + 2);
            }
        }
        for(size_t i = 0; i < nRows; ++i) {
            for(size_t j = 0; j < nCols; ++j) {
                REQUIRE(matrix_2[i][j] == (i + 1) * (j + 2));
            }
        }
    }

    SECTION( "test out of range exception" ) {
        Matrix matrix(2, 2);

        REQUIRE_THROWS_AS(matrix[2][0] = 3, std::out_of_range);
        REQUIRE_THROWS_AS(matrix[0][5] = 8, std::out_of_range);
        REQUIRE_THROWS_AS(matrix[2][0] > 3, std::out_of_range);
        REQUIRE_THROWS_AS(matrix[0][5] <= 8, std::out_of_range);
    }

    SECTION( "test *= operator" ) {
        Matrix matrix(2, 2);
        matrix[0][0] = 1;
        matrix[0][1] = 2;
        matrix[1][0] = 3;
        matrix[1][1] = 4;

        matrix *= 3;

        REQUIRE(matrix[0][0] == 3);
        REQUIRE(matrix[0][1] == 6);
        REQUIRE(matrix[1][0] == 9);
        REQUIRE(matrix[1][1] == 12);
    }

    SECTION( "test == and != operators" ) {
        size_t nRows = 7;
        size_t nCols = 12;
        Matrix matrix_1(nRows, nCols);
        Matrix matrix_2(nRows, nCols);
        for(size_t i = 0; i < nRows; ++i) {
            for(size_t j = 0; j < nCols; ++j) {
                matrix_1[i][j] = (i + 1) * (j + 2);
                matrix_2[i][j] = (i + 1) * (j + 2);
            }
        }

        REQUIRE(matrix_1 == matrix_1);
        REQUIRE(matrix_1 == matrix_2);

        Matrix matrix_3(matrix_1);

        REQUIRE(matrix_3 == matrix_2);

        matrix_3 *= 10;

        REQUIRE(matrix_3 != matrix_2);

        Matrix matrix_4(1, 2);
        matrix_4[0][0] = 0;
        matrix_4[0][1] = 0;
        Matrix matrix_5(2, 1);
        matrix_5[0][0] = 0;
        matrix_5[1][0] = 0;

        REQUIRE(matrix_4 != matrix_5);
    }

    SECTION( "test operations with const matrix" ) {
        Matrix matrix_1(2, 2);
        matrix_1[0][0] = 1;
        matrix_1[0][1] = 2;
        matrix_1[1][0] = 3;
        matrix_1[1][1] = 4;

        const Matrix matrix_2(matrix_1);

        // компилятор проверяет запрет на изменение константной матрицы
        // matrix_2[0][0] = 1; // ошибка компиляции
        // matrix_2 *= 7; // ошибка компиляции

        REQUIRE(matrix_1 == matrix_2);

        REQUIRE(matrix_2[0][0] == 1);
        REQUIRE(matrix_2[0][1] == 2);
        REQUIRE(matrix_2[1][0] == 3);
        REQUIRE(matrix_2[1][1] == 4);

        matrix_1 *= 4;

        REQUIRE(matrix_2 != matrix_1);
    }
}

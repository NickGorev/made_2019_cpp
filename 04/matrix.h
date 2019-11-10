#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <stdexcept>

class Proxy_row {
    public:
        Proxy_row(int* row_data, size_t cols)
            : row_data_(row_data), cols_(cols) {}
        const int& operator[](size_t col) const;
        int& operator[](size_t col);
    private:
        int* row_data_;
        size_t cols_;
};

class Matrix {
    public:
        Matrix(size_t rows, size_t cols);
        Matrix(const Matrix& m);
        ~Matrix();

        size_t getRows(void) const { return rows_; }
        size_t getColumns(void) const { return cols_; }

        const Proxy_row operator[](size_t row) const;
        Proxy_row operator[](size_t row);

        Matrix& operator *= (int scalar);

        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;

    private:
        size_t rows_;
        size_t cols_;
        int* data_;
};

#endif /* MATRIX_H_ */

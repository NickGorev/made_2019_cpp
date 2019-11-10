#include "matrix.h"

const int& Proxy_row::operator[](size_t col) const {
    if (col >= cols_) {
        throw std::out_of_range("");
    }
    return row_data_[col];
};

int& Proxy_row::operator[](size_t col) {
    if (col >= cols_) {
        throw std::out_of_range("");
    }
    return row_data_[col];
};


Matrix::Matrix(size_t rows, size_t cols)
    : rows_(rows), cols_(cols) {
    data_ = new int[rows * cols];
}
Matrix::Matrix(const Matrix& m)
    : rows_(m.rows_), cols_(m.cols_) {
    data_ = new int[rows_ * cols_];
    for(size_t i = 0; i < rows_ * cols_; ++i) {
        data_[i] = m.data_[i];
    }
}


Matrix::~Matrix() {
    delete[] data_;
}

const Proxy_row Matrix::operator[](size_t row) const {
    if (row >= rows_) {
        throw std::out_of_range("");
    }
    return Proxy_row(data_ + row * cols_, cols_);
}

Proxy_row Matrix::operator[](size_t row) {
    if (row >= rows_) {
        throw std::out_of_range("");
    }
    return Proxy_row(data_ + row * cols_, cols_);
};

Matrix& Matrix::operator *= (int scalar) {
    for(size_t i = 0; i < rows_ * cols_; ++i) {
        data_[i] *= scalar;
    }
    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    if (this == &other)
        return true;

    if(rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }

    for (size_t i = 0; i < rows_ * cols_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

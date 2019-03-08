#include "matrix.h"

void Matrix::init_data() {
    int* tmp = new int[_rows * _cols];
    _data = new int*[_rows];

    for (size_t i = 0; i < _rows; ++i) {
        _data[i] = (tmp + i * _cols);
    }
}

void Matrix::set_data(int val) {
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            _data[i][j] = val;
        }
    }
}

void Matrix::clear_data(Matrix &m) {
    delete[](m._data[0]);
    delete[](m._data);
}

Matrix::Matrix(std::size_t r, std::size_t c) : _rows(r), _cols(c){
    init_data();
    set_data(0);
}

Matrix::~Matrix() {
    clear_data(*this);
}

std::size_t Matrix::get_rows() const{ return _rows; }
std::size_t Matrix::get_cols() const{ return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    return _data[i][j];
}

void Matrix::print(FILE* f) const{
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            fprintf(f, "%d ", _data[i][j]);
        }
        fprintf(f, "\n");
    }
}

bool Matrix::operator==(const Matrix& m) const {

    if (_rows != m._rows || _cols != m._cols) {
        return false;
    }

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            if (_data[i][j] != m._data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
    return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            _data[i][j] += m._data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            _data[i][j] -= m._data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    Matrix a(_rows, m._cols);
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < m._cols; ++j) {
            for (size_t k = 0; k < _cols; ++k) {
                a._data[i][j] += _data[i][k] * m._data[k][j];
            }
        }
    }
    *this = a;
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const{
    Matrix a(*this);
    a += m;
    return a;
}

Matrix Matrix::operator-(const Matrix& m) const{
    Matrix a(*this);
    a -= m;
    return a;
}

Matrix Matrix::operator*(const Matrix& m) const{
    Matrix a(*this);
    a *= m;
    return a;
}

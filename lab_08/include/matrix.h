//
// Created by S_P_ on 19.11.18.
//

#ifndef CLION_MATRIX_H
#define CLION_MATRIX_H


#include <cstdio>
#include <cstddef>
#include <algorithm>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);

    ~Matrix();

    Matrix(const Matrix& m) : _rows(m._rows), _cols(m._cols) {
        init_data();
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                _data[i][j] = m._data[i][j];
            }
        }
    }

    void clear_data(Matrix& m);
    void init_data();

    std::size_t get_rows() const;
    std::size_t get_cols() const;

    void set_data(int val);
    void set(std::size_t i, std::size_t j, int val);
    int get(std::size_t i, std::size_t j) const;

    void print(FILE *f) const;

    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;

    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);

    void swap(Matrix &m) {
        std::swap(_cols, m._cols);
        std::swap(_rows, m._rows);
        std::swap(_data, m._data);
    }

    Matrix& operator =(const Matrix &m) {
        if( this != &m) {
            Matrix tmp(m);
            tmp.swap(*this);
        }
        return *this ;
    }

    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;
private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
};


#endif //CLION_MATRIX_H

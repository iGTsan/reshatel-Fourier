#pragma once
#include <vector>
#include <iostream>

using ::std::cout;
using ::std::endl;

using ::std::vector;

// class for algebra matrix
template<typename T>
class Matrix
{
private:
    vector<vector<T>> data_;
    int w_; // number of rows
    int h_; // number of columns
public:
    Matrix(int w, int h) : w_(w), h_(h) {
        data_.resize(w);
        for (auto& it: data_)
            it.resize(h);
    }

    Matrix(const vector<vector<T>>& data) : w_(data.size()), h_(data[0].size()), data_(data) {};
    Matrix(const vector<T>& data) : w_(data.size()), h_(1) {
        data_.resize(w_);
        for (int i = 0; i < w_; i++) {
            data_[i].resize(h_);
            data_[i][0] = data[i];
        }   
    }

    vector<T>& operator[] (int i) {
        return data_[i];
    }

    const vector<T>& operator[] (int i) const {
        return data_[i];
    }

    Matrix operator+(const Matrix& other) {
        if (h_ != other.h_ || w_ != other.w_)
            throw "Can't combine different matrices";
        Matrix result(w_, h_);
        for (int i = 0; i < w_; i++)
            for (int j = 0; j < h_; j++) {
                result[i][j] = other[i][j] + data_[i][j];
            }
        return result;
    }

    Matrix operator*(const Matrix& other) {
        if (h_ != other.w_)
            throw "Can't multiply different matrices";
        Matrix result(w_, other.h_);
        for (int i = 0; i < w_; i++)
            for (int j = 0; j < other.h_; j++) {
                T tmp{};
                for (int k = 0; k < h_; k++) {
                    // cout << data_[i][k] << " * " << other[k][j] << " = " << data_[i][k] * other[k][j] << endl;
                    tmp += data_[i][k] * other[k][j];
                    // cout << tmp << endl;
                }
                result[i][j] = tmp;
            }
        return result;
    }

    Matrix operator*(const vector<T>& other) {
        return *this * Matrix<T>{other};
    }

    Matrix operator/(int x) {
        Matrix result(w_, h_);
        for (int i = 0; i < w_; i++)
            for (int j = 0; j < h_; j++) {
                result[i][j] = data_[i][j] / x;
            }
        return result;
    }

    size_t size() const { 
        return w_;
    }

    size_t size_h() const { 
        return h_;
    }

    void print() const {
        cout << "size: " << w_ << ' ' << h_ << endl;
        for (int i = 0; i < w_; i++) {
            for (int j = 0; j < h_; j++) {
                cout << data_[i][j] << ' ';
            }
            cout << endl;
        }
    }
};


template<typename To, typename From>
Matrix<To> transform_matrix(Matrix<From> matrix) {
    Matrix<To> result(matrix.size(), matrix.size_h());
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix.size_h(); j++)
            result[i][j] = static_cast<To>(matrix[i][j]);
    return result;
}


namespace tests {

void test_mult_int() {
    vector<vector<int>> data1 = {{1, 2}, {3, 4}};
    vector<vector<int>> data2 = {{1, 2}, {3, 4}};
    Matrix<int> matrix1(data1);
    Matrix<int> matrix2(data2);
    matrix1.print();
    matrix2.print();
    auto matrix3_ = matrix1 * matrix2;
    matrix3_.print();
    vector<vector<int>> data3 = {{1, 2, 3}, {3, 4, 5}};
    vector<vector<int>> data4 = {{1, 2, 3, 4}, {3, 4, 5, 6}, {7, 8, 9, 0}};
    Matrix<int> matrix3(data3);
    Matrix<int> matrix4(data4);
    matrix3.print();
    matrix4.print();
    auto matrix5 = matrix3 * matrix4;
    matrix5.print();
}

}

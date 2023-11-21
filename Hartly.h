#pragma once

#include "Matrix.h"
#include "Complex.h"

#include <cmath>

#define PI 3.14159265

double calc_H_i_j(int N, int i, int j) {
    double n = i*j;

    return double{
        cos(n * 2*PI / N) +
        sin(n * 2*PI / N)
    };
}

Matrix<double> calc_H(int N) {
    Matrix<double> result(N, N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            result[i][j] = calc_H_i_j(N, i, j);
    return result;
}

Matrix<double> calc_Hartly(const Matrix<double>& x) {
    int N = x.size();
    auto W = calc_H(N);
    return W*x;
}

Matrix<double> calc_rev_Hartly(const Matrix<double>& x) {
    int N = x.size();
    auto W = calc_H(N);
    return W*x/N;
}

Matrix<double> calc_Hartly(vector<double>& x) {
    return calc_Hartly(Matrix<double>{x});
}


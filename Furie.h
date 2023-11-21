#pragma once

#include "Matrix.h"
#include "Complex.h"

#include <cmath>

#define PI 3.14159265

Complex calc_W_i_j(int N, int i, int j) {
    double n = i*j;

    return Complex{
        cos(-n * 2*PI / N),
        sin(-n * 2*PI / N),
    };
}

Matrix<Complex> calc_W(int N) {
    Matrix<Complex> result(N, N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            result[i][j] = calc_W_i_j(N, i, j);
    return result;
}

Matrix<Complex> calc_Furie(const Matrix<Complex>& x) {
    int N = x.size();
    auto W = calc_W(N);
    return W*x;
}

Matrix<Complex> calc_Furie(vector<Complex>& x) {
    return calc_Furie(Matrix<Complex>{x});
}

Matrix<Complex> sopr(const Matrix<Complex>& v) {
    vector<Complex> res;
    for (int i = 0; i < v.size(); i++)
        res.push_back(v[i][0].sopr());
    return res;
}

Matrix<Complex> sopr(const vector<Complex>& v) {
    return sopr(Matrix<Complex>{v});
}

Matrix<Complex> calc_rev_Furie(const Matrix<Complex>& X) {
    auto x_sopr = sopr(X);
    auto g = calc_Furie(x_sopr);
    auto g_sopr = sopr(g);
    auto x = g_sopr / X.size();
    return x;
}


namespace tests {


void test_Furie_calc_W() {
    auto W3 = calc_W(3);
    W3.print();
    auto W4 = calc_W(4);
    W4.print();
}

void test_Furie_calc() {
    vector<Complex> x = {1, 2, 6, 3};
    auto X = calc_Furie(x);
    X.print();
}

void test_rev_Furie() {
    vector<Complex> X = {{0, 2}, {2}, {5, -2}, {1, 4}};
    auto X_sopr = sopr(X);
    // X_sopr.print();

    auto G = calc_Furie(X_sopr);
    // G.print();

    auto G_sopr = sopr(G);
    // G_sopr.print();

    auto x = G_sopr / 4;
    // cout << "x:" << endl;
    x.print();

    auto X_agan = calc_Furie(x);
    // X_agan.print();

    auto another_x = calc_rev_Furie(X);
    another_x.print();
}

}
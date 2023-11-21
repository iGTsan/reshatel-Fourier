#include <vector>
#include "Hartly.h"
#include "Furie.h"

using ::std::vector;

template<typename T>
vector<T> extrapolating(Matrix<T> x, int m) {
    int N = x.size();
    vector<T> y(N*m);
    y[0] = x[0][0] * m;
    for (int i = 0; i < (N - 1) / 2; i++) {
        y[i + 1] = x[i + 1][0] * m;
        y[N*m - i - 1] = x[N - i - 1][0] * m;
    }
    if (N % 2 == 0) {
        y[N / 2] = x[N / 2][0];
        y[N*m - N / 2] = x[N / 2][0];
    }
    return y;
    
}

template <typename T>
Matrix<T> extapolate_w_Hartly(Matrix<T> x, int m) {
    Matrix<T> y = calc_Hartly(x);
    y = extrapolating(y, m);
    y = calc_rev_Hartly(y);
    return y;
}

template <typename T>
Matrix<T> extapolate_w_Furie(Matrix<T> x, int m) {
    Matrix<T> y = calc_Furie(x);
    y = extrapolating(y, m);
    y = calc_rev_Furie(y);
    return y;
}

namespace tests {

template<typename T>
void print(vector<T> x) {
    for (auto it : x) {
        cout << it << " ";
    }
    cout << endl;
}


void test_extrapolating() {
    vector<double> x = {14, -8, -4, 2};
    auto y = extrapolating(Matrix<double>(x), 2);
    print(x);
    print(y);
}


void test_extrapolating_seq() {
    vector<double> x = {1, 2, 4, 7};
    auto matrix_x = Matrix<double>(x);
    auto y = extapolate_w_Hartly(matrix_x, 2);
    auto z = extapolate_w_Furie(transform_matrix<Complex, double>(matrix_x), 2);
    matrix_x.print();
    y.print();
    z.print();
}


void test_extrapolating_seq2() {
    vector<double> x = {1, 2, 4, 7, 8};
    auto matrix_x = Matrix<double>(x);
    auto y = extapolate_w_Hartly(matrix_x, 3);
    auto z = extapolate_w_Furie(transform_matrix<Complex, double>(matrix_x), 3);
    matrix_x.print();
    y.print();
    z.print();
}

    
} // namespace tests

#include "Furie.h"
#include "Hartly.h"
#include "Extrapolating.h"

void dz_5_Furie() {
    vector<Complex> X = {{0, 2}, {2}, {5, -2}, {1, 4}};
    auto X_sopr = sopr(X);
    X_sopr.print();

    auto G = calc_Furie(X_sopr);
    G.print();

    auto G_sopr = sopr(G);
    G_sopr.print();

    auto x = G_sopr / 4;
    cout << "x:" << endl;
    x.print();

    auto X_agan = calc_Furie(x);
    X_agan.print();
}

void dz_5_Hartly() {
    vector<double> x = {1, 2, 3, 6};

    auto X = calc_Hartly(x);
    X.print();
}

void KR_furie() {
    vector<Complex> x = {1, 6, 3, 2, 4, 0, 7, 2};

    auto X = calc_Furie(x);
    X.print();
}

void KR_Hartly() {
    vector<double> h_1 = {2, 6, 3, 1};
    vector<double> h_2 = {2, 5, 0, 3};
    vector<double> h_3 = {3, 4, 1, 2};

    auto H_1 = calc_Hartly(h_1);
    auto H_2 = calc_Hartly(h_2);
    auto H_3 = calc_Hartly(h_3);
    H_1.print();
    H_2.print();
    H_3.print();
}

void KR_harmonic() {
    vector<Complex> x = {1, 2, 3, 6, 4, 0, 3, -1, -5, -2, 2, 3};

    auto X = calc_Furie(x);
    cout << X[3][0] << endl;
}

int main() {
    // KR_harmonic();
    tests::test_extrapolating_seq();
}
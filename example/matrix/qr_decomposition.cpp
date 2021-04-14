//
// Created by abakfja on 3/21/21.
//

#include <boost/numeric/ublas/matrix/matrix.hpp>
#include <iostream>

using namespace boost::numeric::ublas::experimental;

template<typename T>
auto qr(dmatrix<T> A) {
    auto[m, n] = A.size();
    auto Q = zeros<T>(m, n);
    auto R = zeros<T>(n, n);
    for (std::size_t k = 0; k < n; k++) {
        dmatrix<T> v = A({0, m}, k);
        if (k > 0) {
            R({0, k}, k) = transpose(Q({0, m}, {0, k})) * A({0, m}, k);
            v = A({0, m}, k) - Q({0, m}, {0, k}) * R({0, k}, k);
        }
        R(k, k) = norm<float>(v);
        Q({0, m}, k) = v / R(k, k);
    }
    return std::make_pair(Q, R);
}

int main() {
    dmatrix<float> A{
            {1, 2, 2},
            {3, 3, 3},
            {4, 5, 6},
    };
    auto[Q, R] = qr(A);
    for (int i = 0; i < Q.rows(); i++) {
        for (int j = 0; j < Q.cols(); j++) {
            std::cout << Q(i, j) << ", ";
        }
        std::cout << std::endl;
    }
    dmatrix<float> Qt = transpose(Q);
    auto I = Q * Qt;
    for (int i = 0; i < I.rows(); i++) {
        for (int j = 0; j < I.cols(); j++) {
            std::cout << std::round(I(i, j)) << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "Q is orthogonal" << std::endl;
    for (int i = 0; i < R.rows(); i++) {
        for (int j = 0; j < R.cols(); j++) {
            std::cout << R(i, j) << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << (A == Q * R) << std::endl;
}

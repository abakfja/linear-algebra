//
// Created by abakfja on 3/21/21.
//

#include <boost/numeric/ublas/matrix/matrix.hpp>
#include <iostream>

using namespace boost::numeric::ublas::experimental;

template<typename T>
auto qr(dmatrix<T> A) {
    auto[m, n] = A.size();
    auto Q = dmatrix<T>(m, n);
    auto R = dmatrix<T>(m, n);
    for (std::size_t k = 0; k < n; k++) {
        auto v = A({0, m}, k);
        if (k > 0) {
            R({0, k - 1}, k) = transpose(Q({0, m}, {0, k - 1})) * A({0, m}, k);
            v = A({0, m}, k) - Q({0, m}, {0, k - 1}) * R({0, k - 1}, k);
        }
        R(k, k) = norm<float>(v);
        Q({0, m}, k) = v / R(k, k);
    }
    return std::make_pair(Q, R);
}

int main() {
    dmatrix<float> A {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    auto [Q, R] = qr(A);
    for (int i = 0; i < Q.rows(); i++) {
        for (int j = 0; j < Q.cols(); j++) {
            std::cout << Q(i,j) << ", ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < R.rows(); i++) {
        for (int j = 0; j < R.cols(); j++) {
            std::cout << R(i,j) << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << (A == Q * R) << std::endl;
}

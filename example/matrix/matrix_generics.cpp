//
// Created by abakfja on 3/12/21.
//
#include <iostream>
#include <boost/numeric/ublas/matrix/matrix.hpp>

using namespace boost::numeric::ublas::experimental;


int main() {
    using fmatrix33 = fmatrix<int, 3, 3>;

    // construction using initializer list
    dmatrix<int> a{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    // construction by providing size of the matrix
    dmatrix<int> m(2, 3);

    // construction using initializer list
    fmatrix33 b{
            {1, 2, 3},
            {4, 3, 6},
            {7, 3, 3}
    };

    // size returned as a pair
    auto[r, c]  = a.size();
    std::cout << "size of matrix a:" << r << "," << c << std::endl;

    // equality operator
    std::cout << (a == b) << std::endl;

    // copy assignment
    a = b;
    std::cout << (a == b) << std::endl;

    // converting from different value type
    b = fmatrix33{
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
    };
    std::cout << (a == b + a) << std::endl;

    for (int i = 0; i < a.rows(); i++) {
        for (int j = 0; j < a.cols(); j++) {
            std::cout << a(i, j) << " "; // dereference via () operator
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < a.rows(); i++) {
        for (int j = 0; j < a.cols(); j++) {
            a(i, j) = 0; // assign via () operator
        }
    }

    for (int i = 0; i < a.data_size(); i++) { // data_size return rows * cols
        std::cout << a[i] << " "; // assign via [] using zero based index
    }
}

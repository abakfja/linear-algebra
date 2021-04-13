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
    dmatrix<int> m {
            {3, 4},
            {4, 5},
            {5, 6}
    };

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

    a = b;
    a = a + b * 2 + b * 3;
    std::cout << (a == b * 6) << std::endl;

    // b to be identity matrix
    b = fmatrix33{
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
    };
    auto z = b({0, 2}, {0, 2});
    std::cout << z.rows() << " " << z.cols() << std::endl;
    z = dmatrix<int> {{1, 2}, {3, 4}};
    b({1,3}, {1, 3}) = z;
    for (int i = 0; i < b.rows(); i++) {
        for (int j = 0; j < b.cols(); j++) {
            std::cout << b(i, j) << " "; // dereference via () operator
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

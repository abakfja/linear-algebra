//
// Created by vect on 4/13/21.
//

#include <boost/numeric/ublas/matrix/vector.hpp>

#include <iostream>

using namespace la;

int main() {
    using fvector3 = fvector<int, 3>;

    // construction using initializer list
    dvector<int> a{1, 2, 3};

    // construction using size of vector
    dvector<int> m(3);

    // construction using initializer list
    fvector3 b{1, 1, 3};

    auto l = a.size();
    std::cout << "size of vector a" << l << std::endl;

    // equality operator
    std::cout << (a == b) << std::endl;

    // copy assignment
    a = b;
    std::cout << (a == b) << std::endl;

    b = fvector3{0, 0, 0};

    // iterator
    for (auto &it: a) {
        std::cout << it << " ";
    }

    // assignment using [] operator
    for (auto &it: b) {
        it = 12;
    }
    std::cout << std::endl;

    // dereference using [] operator
    for (int i = 0; i < b.size(); i++) {
        std::cout << b[i] << " ";
    }
}

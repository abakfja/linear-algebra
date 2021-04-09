//
// Created by abakfja on 3/12/21.
//
#include <iostream>
//#include <boost/numeric/ublas/matrix/matrix.hpp>
#include <boost/numeric/ublas/matrix/vector.hpp>
//#include <vector>

class vector_span {

};

using namespace boost::numeric::ublas::experimental;

using fvector = vector<fixed_vector_engine<int, 5>>;

int main() {
    fvector b{1, 2, 3, 4, 5};
    fvector c{5, 4, 3, 2, 1};
    auto a = b({0, 2});
    c({0, 2}) = a;
    for (auto &x: c) {
        std::cout << x << std::endl;
    }
}

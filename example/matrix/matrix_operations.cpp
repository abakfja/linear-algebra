//
// Created by fragrant on 3/12/21.
//
#include <iostream>
#include <boost/numeric/ublas/matrix/matrix/matrix.hpp>
#include <boost/numeric/ublas/matrix/vector/vector.hpp>
#include <vector>

using namespace boost::numeric::ublas::experimental;

int main() {
    matrix<static_matrix_engine<int, 3, 2>> m{1, 2, 3,
                                              4, 5, 6};
    matrix<dynamic_matrix_engine<int>> n(1, 2);
    n.fill(12);
    for (auto x: n) {
        std::cout << x << std::endl;
    }

    vector<dynamic_vector_engine<int, layout::row_major>> a{1, 2, 3};
    vector<static_vector_engine<int, 10, layout::row_major>> v2{1, 2, 3};

}

//
// Created by fragrant on 3/12/21.
//

#include <boost/numeric/ublas/matrix/dynamic_matrix.hpp>
#include <boost/numeric/ublas/matrix/static_matrix.hpp>
#include <boost/numeric/ublas/vector/vector.hpp>
#include <boost/numeric/ublas/matrix/matrix_expression.hpp>
#include <iostream>

using namespace boost::numeric::ublas::experimental;

int main() {
    dynamic_matrix<int> n{{
                          {1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9}
                  }};
    std::cout << n(1, 2) << std::endl;
//    n.print();
}

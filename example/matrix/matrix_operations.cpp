//
// Created by fragrant on 3/12/21.
//
#include <iostream>
#include <boost/numeric/ublas/matrix/matrix.hpp>
#include <boost/numeric/ublas/matrix/vector.hpp>

using namespace boost::numeric::ublas::experimental;
using fvector = vector<fixed_vector_engine<double, 4>>;
template<typename T>
using dvector = vector<dynamic_vector_engine<T>>;

int main() {

//    auto b = fixed_matrix_engine<double, 5, 4>{{1, 2, 3},
//                                               {4, 5, 6}};
//    auto c = dynamic_matrix_engine<float>(b);
//    b = fixed_matrix_engine<double, 5, 4>{{3, 2, 3, 4},
//                                          {4, 5, 6, 7}};;
    auto b = fvector(10.12);
    auto d(b);
    auto c = dvector<double>{1,1,1,1};
    auto x = b.size();
    auto y = c.size();
    std::cout << x << " " << y << std::endl;
    fvector z = c * b;
    std::cout << z.size() << " " << b.size() << std::endl;
    assert(z == b);
    for (auto& xx: z) {
        std::cout << xx << " ";
    }
}

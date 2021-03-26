//
//  Copyright (c) 2021 Kannav Mehta
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UBLAS_MATRIX_EXPRESSION_HPP
#define UBLAS_MATRIX_EXPRESSION_HPP

#include <boost/numeric/ublas/matrix/traits/matrix_traits.hpp>
#include <type_traits>


namespace boost::numeric::ublas::experimental::detail {

/**
 * @brief Template class to store both unary and binary matrix expressions
 * 
 * @tparam callable The function object for the respective expression
 * @tparam operands The one or two operands for the expression
 */
template<class callable, class... operands>
class matrix_expression {
    using expr_t = callable;
public:
    explicit matrix_expression(callable f, operands const &... args) : f(f), args(args...) {}

private:
    callable f;
    std::tuple<operands const &...> args;
};

template<class L, class R>
auto operator*(const L &l, const R &r) {
    return matrix_expression{[](const L &l, const R &r) {
        return l * r;
    }, l, r};
}

}
#endif //UBLAS_MATRIX_EXPRESSION_HPP

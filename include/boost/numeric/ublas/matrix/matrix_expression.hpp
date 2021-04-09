//
// Created by abakfja on 4/4/21.
//

#ifndef UBLAS_MATRIX_EXPRESSION_HPP
#define UBLAS_MATRIX_EXPRESSION_HPP

#include <boost/numeric/ublas/matrix/traits/expression_traits.hpp>
#include <tuple>

namespace boost::numeric::ublas::experimental {
    
} // boost::numeric::ublas::experimental


namespace boost::numeric::ublas::experimental {

template<typename operand>
constexpr inline auto index_op(operand a, std::size_t idx) {
    if constexpr(detail::is_matrix_or_expr_v<operand>) {
        return a(n, m);
    } else {
        return a;
    }
}

template<typename operand>
constexpr inline std::size_t expr_rows(operand a) {
    if constexpr(detail::is_matrix_or_expr_v<operand>) {
        return a.rows();
    } else {
        return 0;
    }
}

template<typename operand>
constexpr inline std::size_t expr_cols(operand a) {
    if constexpr(detail::is_matrix_or_expr_v<operand>) {
        return a.cols();
    } else {
        return 0;
    }
}


template<typename operation, typename ... operands>
class matrix_expr {
public:
    explicit matrix_expr(operation f_, operands const &... args_) : f(f_), args(args_...) {}

    auto operator[](std::size_t n, std::size_t m) const {
        return std::apply([this, n, m](operands const &... a) {
            return f(index_op(a, n, m)...);
        }, args);
    }

    [[nodiscard]] constexpr std::pair<std::size_t, std::size_t> size() const {
        return std::apply([this](operands const &... x) {
            std::size_t a{}, b{};
            ((a = std::max(a, expr_rows(x))), ...);
            ((b = std::max(b, expr_cols(x))), ...);
            return make_pair(a, b);
        }, args);
    }

private:
    std::tuple<operands const &...> args;
    operation f;
};


template<class LHS, class RHS, typename = std::enable_if<
        detail::is_bin_vec_op_ok<LHS, RHS>, bool>>
inline decltype(auto) constexpr operator*(const LHS &lhs, const RHS &rhs) {

}

template<class LHS, class RHS, typename = std::enable_if<
        detail::is_bin_vec_op_ok<LHS, RHS>, bool>>
inline decltype(auto) constexpr operator/(const LHS &lhs, const RHS &rhs) {
    return matrix_expr{[](auto a, auto b) {
        return a / b;
    }, lhs, rhs};
}

template<class LHS, class RHS, typename = std::enable_if<
        detail::is_bin_vec_op_ok<LHS, RHS>, bool>>
inline decltype(auto) constexpr operator%(const LHS &lhs, const RHS &rhs) {
    return matrix_expr{[](auto a, auto b) {
        return a % b;
    }, lhs, rhs};
}

template<class LHS, class RHS, typename = std::enable_if<
        detail::is_bin_vec_op_ok<LHS, RHS>, bool>>
inline decltype(auto) constexpr operator+(const LHS &lhs, const RHS &rhs) {
    return matrix_expr{[](auto a, auto b) {
        return a + b;
    }, lhs, rhs};
}

template<class LHS, class RHS, typename = std::enable_if<
        detail::is_bin_vec_op_ok<LHS, RHS>, bool>>
inline decltype(auto) constexpr operator-(const LHS &lhs, const RHS &rhs) {
    return matrix_expr{[](auto a, auto b) {
        return a - b;
    }, lhs, rhs};
}

template<class OP>
inline decltype(auto) constexpr operator-(const OP &op) {
    return matrix_expr{[](auto a) {
        return -a;
    }, op};
}

}

#endif //UBLAS_MATRIX_EXPRESSION_HPP

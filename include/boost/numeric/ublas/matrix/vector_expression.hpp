//
// Created by abakfja on 4/4/21.
//
//
#ifndef UBLAS_VECTOR_EXPRESSION_HPP
#define UBLAS_VECTOR_EXPRESSION_HPP

#include <boost/numeric/ublas/matrix/traits/expression_traits.hpp>
#include <tuple>

namespace boost::numeric::ublas::experimental {

template<typename operand>
constexpr inline auto index_op(operand a, std::size_t idx) {
    if constexpr(detail::is_vector_or_expr_v<operand>) {
        return a[idx];
    } else {
        return a;
    }
}

template<typename operand>
constexpr inline std::size_t expr_size(operand a) {
    if constexpr(detail::is_vector_or_expr_v<operand>) {
        return a.size();
    } else {
        return 0;
    }
}

template<typename operation, typename ... operands>
class vector_expr {
public:
    explicit vector_expr(operation f_, operands const &... args_) : f(f_), args(args_...) {}

    auto operator[](std::size_t idx) const {
        return std::apply([this, idx](operands const &... a) {
            return f(index_op(a, idx)...);
        }, args);
    }

    [[nodiscard]] constexpr std::size_t size() const {
        return std::apply([this](operands const &... x) {
            std::size_t a{};
            ((a = std::max(a, expr_size(x))), ...);
            return a;
        }, args);
    }

private:
    std::tuple<operands const &...> args;
    operation f;
};

template<class LHS, class RHS, typename = std::enable_if<
        detail::is_bin_vec_op_ok<LHS, RHS>, bool>>
inline decltype(auto) constexpr operator+(const LHS &lhs, const RHS &rhs) {
    return vector_expr{[](auto a, auto b) {
        return a + b;
    }, lhs, rhs};
}


template<class LHS, class RHS, typename = std::enable_if<
        detail::is_bin_vec_op_ok<LHS, RHS>, bool>>
inline decltype(auto) constexpr operator/(const LHS &lhs, const RHS &rhs) {
    return vector_expr{[](auto a, auto b) {
        return a / b;
    }, lhs, rhs};
}

template<class LHS, class RHS>
//        std::enable_if_t<
//        detail::is_vector_or_expr_v<LHS> && detail::is_vector_or_expr_v<RHS>, bool> = false>
inline decltype(auto) constexpr operator*(const LHS &lhs, const RHS &rhs) {
    return vector_expr{[](auto a, auto b) {
        return a * b;
    }, lhs, rhs};
}


template<class LHS, class RHS, std::enable_if_t<
        detail::is_vector_or_expr_v<LHS> && detail::is_vector_or_expr_v<RHS>, bool> = true>
inline decltype(auto) constexpr operator*(const LHS &lhs, const RHS &rhs) {
    using value_type = decltype(index_op(lhs, 0) * index_op(rhs, 0));
    using size_type = std::size_t;
    value_type it{};
    check_engine_size(rhs, lhs.size());
    for (size_type i{}; i < lhs.size(); i++) {
        it += index_op(lhs, i) * index_op(rhs, i);
    }
    return it;
}


template<class LHS, class RHS, typename = std::enable_if<
        detail::is_bin_vec_op_ok<LHS, RHS>, bool>>
inline decltype(auto) constexpr operator-(const LHS &lhs, const RHS &rhs) {
    return vector_expr{[](auto a, auto b) {
        return a - b;
    }, lhs, rhs};
}

template<class OP>
inline decltype(auto) constexpr operator-(const OP &op) {
    return vector_expr{[](auto a) {
        return -a;
    }, op};
}

}


#endif //UBLAS_VECTOR_EXPRESSION_HPP

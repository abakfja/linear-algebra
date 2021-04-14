//
// Created by abakfja on 4/14/21.
//

#ifndef UBLAS_VECTOR_OPERATORS_HPP
#define UBLAS_VECTOR_OPERATORS_HPP

#include <boost/numeric/ublas/matrix/vector_expression.hpp>
#include <cmath>

namespace boost::numeric::ublas::experimental {
template<typename LHS, typename RHS>
inline decltype(auto) constexpr
operator+(const base_vector_expression <LHS> &lhs, const base_vector_expression <RHS> &rhs) {
    if (lhs.size() != rhs.size()) {
        throw std::runtime_error("Invalid vectors for addition");
    }
    return vector_expression([](auto a, auto b) {
        return a + b;
    }, *static_cast<const LHS *>(&lhs), *static_cast<const RHS *>(&rhs));
}


template<typename LHS, typename RHS>
inline decltype(auto) constexpr
operator-(const base_vector_expression <LHS> &lhs, const base_vector_expression <RHS> &rhs) {
    if (lhs.size() != rhs.size()) {
        throw std::runtime_error("Invalid vectors for addition");
    }
    return vector_expression([](auto a, auto b) {
        return a - b;
    }, *static_cast<const LHS *>(&lhs), *static_cast<const RHS *>(&rhs));
}


template<typename LHS, typename RHS, std::enable_if_t<std::is_arithmetic_v<LHS>, bool> = true>
inline decltype(auto) constexpr
operator*(const LHS &lhs, const base_vector_expression <RHS> &rhs) {
    return vector_expression([](auto a, auto b) {
        return a * b;
    }, lhs, *static_cast<const RHS *>(&rhs));
}


template<typename LHS, typename RHS, std::enable_if_t<std::is_arithmetic_v<RHS>, bool> = true>
inline decltype(auto) constexpr
operator*(const base_vector_expression <LHS> &lhs, const RHS &rhs) {
    return vector_expression([](auto a, auto b) {
        return a * b;
    }, *static_cast<const LHS *>(&lhs), rhs);
}


template<typename LHS, typename RHS, std::enable_if_t<std::is_arithmetic_v<LHS>, bool> = true>
inline decltype(auto) constexpr
operator/(const LHS &lhs, const base_vector_expression <RHS> &rhs) {
    return vector_expression([](auto a, auto b) {
        return a / b;
    }, lhs, *static_cast<const RHS *>(&rhs));
}


template<typename LHS, typename RHS, std::enable_if_t<std::is_arithmetic_v<RHS>, bool> = true>
inline decltype(auto) constexpr
operator/(const base_vector_expression <LHS> &lhs, const RHS &rhs) {
    return vector_expression([](auto a, auto b) {
        return a / b;
    }, *static_cast<const LHS *>(&lhs), rhs);
}

template<typename LHS, typename RHS>
inline decltype(auto) constexpr
operator*(const base_vector_expression <LHS> &lhs, const base_vector_expression <RHS> &rhs) {
    if (lhs.size() != rhs.size()) {
        throw std::runtime_error("vector multiplication ill-defined");
    }
    return vector_expression([](auto a, auto b) {
        return a * b;
    }, *static_cast<const LHS *>(&lhs), rhs);
}

template<typename LHS, typename RHS>
inline decltype (auto) constexpr
inner_product(const base_vector_expression<LHS> &lhs, const base_vector_expression<RHS> &rhs) {
    if (lhs.size() != rhs.size()) {
        throw std::runtime_error("vector multiplication ill-defined");
    }
    using value_type = decltype(lhs(0, 0) * rhs(0, 0));
    value_type res{};
    for (std::size_t i{}; i < lhs.rows(); i++) {
        res += lhs[i] * rhs[i];
    }
    return res;
}

template<typename ret, typename T, std::enable_if_t<std::is_floating_point_v<ret>, bool> = true>
inline ret constexpr
norm(const base_vector_expression <T> &vect) {
    ret res{};
    for (std::size_t i{}; i < vect.size(); i++) {
            res += vect[i];
    }
    return std::sqrt(res);
}

}
#endif //UBLAS_VECTOR_OPERATORS_HPP

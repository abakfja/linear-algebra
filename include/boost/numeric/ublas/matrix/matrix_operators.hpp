//
// Created by abakfja on 4/13/21.
//

#ifndef UBLAS_MATRIX_OPERATORS_HPP
#define UBLAS_MATRIX_OPERATORS_HPP

#include <boost/numeric/ublas/matrix/matrix_expression.hpp>
#include <cmath>

namespace boost::numeric::ublas::experimental {
template<typename LHS, typename RHS>
inline decltype(auto) constexpr
operator+(const base_matrix_expression<LHS>&lhs, const base_matrix_expression<RHS>&rhs) {
    if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()) {
        throw std::runtime_error("Invalid matrices for addition");
    }
    return matrix_expression([](auto a, auto b) {
        return a + b;
    }, *static_cast<const LHS *>(&lhs), *static_cast<const RHS *>(&rhs));
}


template<typename LHS, typename RHS>
inline decltype(auto) constexpr
operator-(const base_matrix_expression <LHS> &lhs, const base_matrix_expression <RHS> &rhs) {
    if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()) {
        throw std::runtime_error("Invalid matrices for addition");
    }
    return matrix_expression([](auto a, auto b) {
        return a - b;
    }, *static_cast<const LHS *>(&lhs), *static_cast<const RHS *>(&rhs));
}


template<typename LHS, typename RHS, std::enable_if_t<std::is_arithmetic_v<LHS>, bool> = true>
inline decltype(auto) constexpr
operator*(const LHS &lhs, const base_matrix_expression <RHS> &rhs) {
    return matrix_expression([](auto a, auto b) {
        return a * b;
    }, lhs, *static_cast<const RHS *>(&rhs));
}


template<typename LHS, typename RHS, std::enable_if_t<std::is_arithmetic_v<RHS>, bool> = true>
inline decltype(auto) constexpr
operator*(const base_matrix_expression <LHS> &lhs, const RHS &rhs) {
    return matrix_expression([](auto a, auto b) {
        return a * b;
    }, *static_cast<const LHS *>(&lhs), rhs);
}


template<typename LHS, typename RHS, std::enable_if_t<std::is_arithmetic_v<LHS>, bool> = true>
inline decltype(auto) constexpr
operator/(const LHS &lhs, const base_matrix_expression <RHS> &rhs) {
    return matrix_expression([](auto a, auto b) {
        return a / b;
    }, lhs, *static_cast<const RHS *>(&rhs));
}


template<typename LHS, typename RHS, std::enable_if_t<std::is_arithmetic_v<RHS>, bool> = true>
inline decltype(auto) constexpr
operator/(const base_matrix_expression <LHS> &lhs, const RHS &rhs) {
    return matrix_expression([](auto a, auto b) {
        return a / b;
    }, *static_cast<const LHS *>(&lhs), rhs);
}

template<typename LHS, typename RHS>
inline decltype(auto) constexpr
operator*(const base_matrix_expression <LHS> &lhs, const base_matrix_expression <RHS> &rhs) {
    if (lhs.cols() != rhs.rows()) {
        throw std::runtime_error("Matrix multiplication ill-defined");
    }
    using value_type = decltype(lhs(0, 0) * rhs(0, 0));
    auto temp = matrix<dynamic_matrix_engine<value_type>>(lhs.rows(), rhs.cols());
    for (std::size_t i{}; i < lhs.rows(); i++) {
        for (std::size_t j{}; j < rhs.cols(); j++) {
            for (std::size_t k{}; k < lhs.cols(); k++) {
                temp(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
    return temp;
}


template<typename T>
inline decltype(auto) constexpr
transpose(const base_matrix_expression <T> &mat) {
    return transpose_expression(*static_cast<const T *>(&mat));
}

/**
 * Calculate the Euclidean norm of the vector v
 */
template<typename ret = float, typename T, std::enable_if_t<std::is_floating_point_v<ret>, bool> = true>
inline ret constexpr
norm(const base_matrix_expression <T> &mat) {
    ret res{};
    for (std::size_t i{}; i < mat.rows(); i++) {
        for (std::size_t j{}; j < mat.cols(); j++) {
            res += mat(i, j) * mat(i, j);
        }
    }
    return std::sqrt(res);
}

}
#endif //UBLAS_MATRIX_OPERATORS_HPP

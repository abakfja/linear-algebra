//
// Created by abakfja on 4/4/21.
//

#ifndef UBLAS_MATRIX_EXPRESSION_HPP
#define UBLAS_MATRIX_EXPRESSION_HPP

#include <boost/numeric/ublas/matrix/traits/expression_traits.hpp>
#include <tuple>


namespace boost::numeric::ublas::experimental {

template<typename E>
struct base_matrix_expression {
    using expression_type = E;

    constexpr auto operator()(std::size_t x, std::size_t y) const {
        return static_cast<const E &>(*this)(x, y);
    }

    constexpr auto size() const {
        return static_cast<const E &>(*this).size();
    }

    constexpr auto rows() const {
        return static_cast<const E &>(*this).rows();
    }

    constexpr auto cols() const {
        return static_cast<const E &>(*this).cols();
    }
};

namespace detail {
template<typename operand>
constexpr inline auto mat_subscript(const operand &a, std::size_t x, std::size_t y) {
    if constexpr(detail::is_matrix_expr_v<operand>) {
        return a(x, y);
    } else {
        return a;
    }
}


template<typename operand>
constexpr inline std::size_t mat_expr_rows(const operand &a) {
    if constexpr(detail::is_matrix_expr_v<operand>) {
        return a.rows();
    } else {
        return 0;
    }
}


template<typename operand>
constexpr inline std::size_t mat_expr_cols(const operand &a) {
    if constexpr(detail::is_matrix_expr_v<operand>) {
        return a.cols();
    } else {
        return 0;
    }
}

} // namespace detail

template<class operation, typename ... operands>
struct matrix_expression
        : public base_matrix_expression<matrix_expression<operation, operands...>> {

    ~matrix_expression() = default;

    matrix_expression() = default;

    matrix_expression(const matrix_expression &) = delete;

    matrix_expression(matrix_expression &&other) : f(std::move(other.f)), args(other.args) {
    }

    explicit matrix_expression(operation f_, operands const &... args_) : f(f_), args(args_...) {}

    constexpr matrix_expression &operator=(matrix_expression &&l) noexcept = default;

    matrix_expression &operator=(matrix_expression const &l) noexcept = delete;

    constexpr auto operator()(std::size_t x, std::size_t y) const {
        return std::apply([this, x, y](operands const &... a) {
            return f(detail::mat_subscript(a, x, y)...);
        }, args);
    }

    constexpr auto size() const {
        return std::make_pair(rows(), cols());

    }

    constexpr auto rows() const {
        return std::apply([this](operands const &... x) {
            std::size_t a{};
            ((a = std::max(a, static_cast<std::size_t>(detail::mat_expr_rows(x)))), ...);
            return a;
        }, args);
    }

    constexpr auto cols() const {
        return std::apply([this](operands const &... x) {
            std::size_t a{};
            ((a = std::max(a, static_cast<std::size_t>(detail::mat_expr_cols(x)))), ...);
            return a;
        }, args);
    }

    std::tuple<operands const &...> args;
    operation f;
};

template<class T>
struct transpose_expression : public base_matrix_expression<transpose_expression<T>> {
    static_assert(detail::is_matrix_expr_v<T>);
    constexpr transpose_expression &operator=(transpose_expression &&l) noexcept = default;

    transpose_expression &operator=(transpose_expression const &l) noexcept = delete;

    transpose_expression(const T &_mat) : mat(_mat) {}

    constexpr auto operator()(std::size_t x, std::size_t y) const {
        return mat(y, x);
    }

    constexpr auto size() const {
        return std::make_pair(rows(), cols());

    }

    constexpr auto rows() const {
        return mat.cols();
    }

    constexpr auto cols() const {
        return mat.rows();
    }

    const T &mat;
};


}
#endif //UBLAS_MATRIX_EXPRESSION_HPP

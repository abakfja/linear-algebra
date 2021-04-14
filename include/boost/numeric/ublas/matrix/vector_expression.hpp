//
// Created by abakfja on 4/4/21.
//
//
#ifndef UBLAS_VECTOR_EXPRESSION_HPP
#define UBLAS_VECTOR_EXPRESSION_HPP

#include <boost/numeric/ublas/matrix/traits/expression_traits.hpp>
#include <tuple>


namespace boost::numeric::ublas::experimental {

template<typename E>
struct base_vector_expression {
    using expression_type = E;

    constexpr auto operator[](std::size_t x) const {
        return static_cast<const E &>(*this)[x];
    }

    constexpr auto size() const {
        return static_cast<const E &>(*this).size();
    }
};

namespace detail {

template<typename operand>
constexpr inline auto vec_subscript(const operand &a, std::size_t x) {
    if constexpr(detail::is_vector_expr_v<operand>) {
        return a[x];
    } else {
        return a;
    }
}

template<typename operand>
constexpr inline std::size_t vec_expr_size(const operand &a) {
    if constexpr(detail::is_vector_expr_v<operand>) {
        return a.size();
    } else {
        return 0;
    }
}

} // namespace detail

template<class operation, typename ... operands>
struct vector_expression
        : public base_vector_expression<vector_expression<operation, operands...>> {

    ~vector_expression() = default;

    vector_expression() = default;

    vector_expression(const vector_expression &) = delete;

    vector_expression(vector_expression &&other) : f(std::move(other.f)), args(other.args) {
    }

    explicit vector_expression(operation f_, operands const &... args_) : f(f_), args(args_...) {}

    constexpr vector_expression &operator=(vector_expression &&l) noexcept = default;

    vector_expression &operator=(vector_expression const &l) noexcept = delete;

    constexpr auto operator[](std::size_t idx) const {
        return std::apply([this, idx](operands const &... a) {
            return f(detail::vec_subscript(a, idx)...);
        }, args);
    }

    constexpr auto size() const {
        return std::apply([this](operands const &... x) {
            std::size_t a{};
            ((a = std::max(a, static_cast<std::size_t>(detail::vec_expr_size(x)))), ...);
            return a;
        }, args);
    }


    std::tuple<operands const &...> args;
    operation f;
};

} // namespace boost::numeric::ublas::experimental

#endif //UBLAS_VECTOR_EXPRESSION_HPP

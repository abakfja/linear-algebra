//
//  Copyright (c) 2021 Kannav Mehta
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_UBLAS_VECTOR_H
#define BOOST_NUMERIC_UBLAS_VECTOR_H

#include <boost/numeric/ublas/matrix/vector_engine.hpp>
#include <boost/numeric/ublas/matrix/vector_expression.hpp>
#include <boost/numeric/ublas/matrix/traits/layout_traits.hpp>

namespace boost::numeric::ublas::experimental {

template<typename Engine, typename Layout = layout::row_major>
class vector {
public:
    using engine_type = Engine;
    using layout_type = Layout;
    using array_type = typename engine_type::array_type;

    using size_type = typename engine_type::size_type;
    using difference_type = typename engine_type::difference_type;

    using value_type = typename engine_type::value_type;

    using reference = typename engine_type::reference;
    using const_reference = typename engine_type::const_reference;

    using pointer = typename engine_type::pointer;
    using const_pointer = typename engine_type::const_pointer;

    using iterator = typename engine_type::iterator;
    using const_iterator = typename engine_type::const_iterator;

    using reverse_iterator = typename engine_type::reverse_iterator;
    using const_reverse_iterator = typename engine_type::const_reverse_iterator;

    using storage_tag = typename engine_type::storage_tag;

    using transpose_type = vector<typename engine_type::transpose_type,
            typename layout_type::transpose_type> &;
    using const_transpose_type = const vector<typename engine_type::transpose_type,
            typename layout_type::transpose_type> &;

    /**
     * default destructor
     */
    ~vector() = default;

    /**
     * default move constructor
     */
    constexpr vector(vector &&) noexcept = default;

    /**
     * default copy constructor
     */
    constexpr vector(const vector &) = default;

    /**
     * Copy constructor for cross engine conversion of vectors
     * @tparam Engine2 Engine type of the matrix being copied
     * @param other
     */
    template<class Engine2>
    constexpr
    vector(const vector<Engine2, layout_type> &other) : expr_rep(other.size()) {
        assert(expr_rep.size() >= other.size());
        std::copy(other.begin(), other.end(), begin());
    }

    /**
     * c-tor for constructing a vector initializer list. Bounds are checked.
     * @tparam U
     * @param list
     */
    template<typename U>
    constexpr vector(std::initializer_list<U> list): expr_rep(list) {}

    /**
     * c-tor for constructing a dynamic_size_vector of size n
     * and fill with value v;
     * @tparam Engine2
     * @param n number of elements
     * @param v initial value of the vector elements
     */
    template<class Engine2 = engine_type, typename = detail::enable_if_dynamic<Engine2>>
    explicit constexpr vector(size_type n, value_type v = {}) : expr_rep(n) {
        std::fill(expr_rep.begin(), expr_rep.end(), v);
    }

    /**
     * Constructor to create a fixed_size_vector and fill it with a value v
     * @tparam Engine2
     * @param v initial value of the vector
     */
    template<class Engine2 = engine_type, typename = detail::enable_if_static<Engine2>>
    constexpr explicit vector(value_type v): expr_rep() {
        std::fill(expr_rep.begin(), expr_rep.end(), v);
    }

    template<typename operation,
            typename ... operands
    >
    constexpr
    vector(const vector_expr<operation, operands...> expr): expr_rep(expr.size()) {
        assert(size() == expr.size());
        for (size_type i = 0; i < size(); i++) {
            this->operator[](i) = expr[i];
        }
    }

    constexpr vector &operator=(vector &&) noexcept = default;

    constexpr vector &operator=(vector const &) = default;

    // copy assignment
    template<typename engine2>
    constexpr vector &operator=(const vector<engine2, layout_type> &other) {
        if constexpr (detail::is_dynamic_v<engine_type>) {
            expr_rep.resize(other.size());
        } else {
            assert(size() == other.size());
        }
        std::copy(other.begin(), other.end(), expr_rep.begin());
        return *this;
    }

    template<typename operation, typename ... operands>
    constexpr vector &operator=(const vector_expr<operation, operands...> expr) {
        if constexpr (detail::is_dynamic_v<engine_type>) {
            expr_rep.resize(expr.size());
        } else {
            assert(size() == expr.size());
        }
        for (size_type i = 0; i < size(); i++) {
            this->operator[](i) = expr[i];
        }
        return *this;
    }

    template<typename engine2>
    bool operator==(const vector<engine2, layout_type> &other) const {
        assert(size() == other.size());
        for (size_type i = 0; i < size(); i++) {
            if (this->operator[](i) != other[i]) {
                return false;
            }
        }
        return true;
    }

    const_reference operator[](size_type idx) const noexcept {
        return expr_rep[idx];
    }

    reference operator[](size_type idx) noexcept {
        return expr_rep[idx];
    }

    [[nodiscard]]  size_type size() const noexcept {
        return expr_rep.size();
    }

    [[nodiscard]]  bool empty() const noexcept {
        return expr_rep.empty();
    }

    template<class Engine2 = engine_type, typename = detail::enable_if_dynamic<Engine2>>
    void resize(size_type n) {
        expr_rep.resize(n);
    }

    constexpr auto begin() noexcept {
        return expr_rep.begin();
    }

    constexpr auto end() noexcept {
        return expr_rep.end();
    }

    constexpr auto begin() const noexcept {
        return expr_rep.begin();
    }

    constexpr auto end() const noexcept {
        return expr_rep.end();
    }

private:
    engine_type expr_rep;
};

} // namespace boost::numeric::ublas::experimental

#endif // BOOST_NUMERIC_UBLAS_VECTOR_H
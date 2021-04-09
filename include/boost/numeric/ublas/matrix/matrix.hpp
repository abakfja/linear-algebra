//
//  Copyright (c) 2021 Kannav Mehta
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_UBLAS_MATRIX_H
#define BOOST_NUMERIC_UBLAS_MATRIX_H

#include <boost/numeric/ublas/matrix/matrix_engine.hpp>
#include <boost/numeric/ublas/matrix/matrix_expression.hpp>

namespace boost::numeric::ublas::experimental {

template<typename Engine>
class matrix {
public:
    using engine_type = Engine;
    using array_type = typename engine_type::array_type;

    using size_type = typename engine_type::size_type;
    using size_pair = typename engine_type::size_pair;
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

    using transpose_type = matrix<typename engine_type::transpose_type> &;
    using const_transpose_type = const matrix<typename engine_type::transpose_type> &;

    /**
     * default destructor
     */
    ~matrix() = default;

    /**
     * default move constructor
     */
    constexpr matrix(matrix &&) noexcept = default;

    /**
     * default copy constructor
     */
    constexpr matrix(const matrix &) = default;

    /**
     * Copy constructor for cross engine conversion of matrices
     * @tparam Engine2 Engine type of the matrix being copied
     * @param other
     */
    template<class Engine2>
    constexpr
    matrix(const matrix<Engine2> &other) : expr_rep(other.size()) {
        assert(expr_rep.size() == other.size());
        std::copy(other.begin(), other.end(), begin());
    }

    /**
     * c-tor for constructing a matrix from a two-dim initializer list
     * @tparam U 
     * @param list 
     */
    template<typename U>
    constexpr matrix(std::initializer_list<U> list): expr_rep(list) {}

    /**
     * c-tor for constructing a dynamic_size_matrix of size [row][column]
     * and fill with value v;
     * @tparam Engine2 
     * @param row rows of the matrix
     * @param col columns
     * @param v initial value of the matrix elements
     */
    template<typename Engine2=engine_type, typename = detail::enable_if_dynamic<Engine2>>
    explicit constexpr matrix(size_type row, size_type col, value_type v = {}): expr_rep(row, col) {
        std::fill(expr_rep.begin(), expr_rep.end(), v);
    }

    /**
     * c-tor for constructing a dynamic_size_matrix of row * column
     * but using std::pair and fill with value v;
     * @tparam Engine2
     * @param sz A std::pair with the rows as the first element
     * @param v initial value of the matrix elements
     */
    template<typename Engine2=engine_type, typename = detail::enable_if_dynamic<Engine2>>
    explicit constexpr matrix(size_pair sz, value_type v = {}): expr_rep(sz) {
        std::fill(expr_rep.begin(), expr_rep.end(), v);
    }

    /**
     * Constructor to create a fixed_size_matrix and fill it with a value v 
     * @tparam Engine2 
     * @param v 
     */
    template<typename Engine2=engine_type, typename = detail::enable_if_static<Engine2>>
    explicit constexpr matrix(value_type v = {}): expr_rep(v) {
        std::fill(expr_rep.begin(), expr_rep.end(), v);
    }

    template<typename operation,
            typename ... operands
    >
    constexpr
    matrix(const matrix_expr<operation, operands...> expr): expr_rep(expr.size()) {
        assert(size() == expr.size());
        for (size_type i = 0; i < data_size(); i++) {
            this->operator[](i) = expr[i];
        }
    }

    constexpr matrix &operator=(matrix &&) noexcept = default;

    constexpr matrix &operator=(matrix const &) = default;

    /**
     * Assignment operator to convert from a matrix of a different engine
     * @tparam engine2
     * @param other
     */
    template<typename engine2>
    constexpr matrix &operator=(const matrix<engine2> &other) {
        if constexpr (detail::is_dynamic_v<engine_type>) {
            expr_rep.resize(other.size().first, other.size().second);
        } else {
            assert(size() == other.size());
        }
        std::copy(other.begin(), other.end(), expr_rep.begin());
        return *this;
    }

    /**
     * Assignment operator to convert a matrix expression into a matrix type
     *
     * @tparam operation
     * @tparam operands
     * @param expr
     * @return
     */
    template<typename operation, typename ... operands>
    constexpr matrix &operator=(const matrix_expr<operation, operands...> expr) {
        if constexpr (detail::is_dynamic_v<engine_type>) {
            expr_rep.resize(expr.size());
        } else {
            assert(size() == expr.size());
        }
        for (size_type i = 0; i < data_size(); i++) {
            this->operator[](i) = expr[i];
        }
        return *this;
    }

    template<typename engine2>
    constexpr bool operator==(const matrix<engine2> &other) const {
        assert(size() == other.size());
        for (size_type i = 0; i < data_size(); i++) {
            if (this->operator[](i) != other[i]) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr size_type data_size() const noexcept {
        return expr_rep.data_size();
    }

    [[nodiscard]] constexpr size_pair size() const noexcept {
        return expr_rep.size();
    }

    [[nodiscard]] constexpr size_pair rows() const noexcept {
        return expr_rep.n_rows;
    }

    [[nodiscard]] constexpr size_pair cols() const noexcept {
        return expr_rep.n_cols();
    }

    [[nodiscard]] constexpr bool empty() const noexcept {
        return expr_rep.empty();
    }

    template<class Engine2 = engine_type, typename = detail::enable_if_dynamic<Engine2>>
    void resize(size_type r, size_type c) {
        expr_rep.resize(r, c);
    }

    template<class Engine2 = engine_type, typename = detail::enable_if_dynamic<Engine2>>
    void resize(size_pair sz) {
        expr_rep.resize(sz.first, sz.second);
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

#endif // BOOST_NUMERIC_UBLAS_MATRIX_H
//
//  Copyright (c) 2021 Kannav Mehta
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_UBLAS_MATRIX_ENGINE_H
#define BOOST_NUMERIC_UBLAS_MATRIX_ENGINE_H

#include <cstddef>
#include <array>
#include <vector>
#include <tuple>
#include <boost/numeric/ublas/matrix/traits/storage_traits.hpp>
#include <cassert>

namespace boost::numeric::ublas::experimental {

template<typename T, std::size_t R, std::size_t C>
struct fixed_matrix_engine {
    using array_type = std::array<T, R * C>;
    using storage_traits_type = storage_traits<array_type>;

    using size_type = typename storage_traits_type::size_type;
    using size_pair = std::pair<size_type, size_type>;
    using difference_type = typename storage_traits_type::difference_type;

    using value_type = typename storage_traits_type::value_type;

    using reference = typename storage_traits_type::reference;
    using const_reference = typename storage_traits_type::const_reference;

    using pointer = typename storage_traits_type::pointer;
    using const_pointer = typename storage_traits_type::const_pointer;

    using iterator = typename storage_traits_type::iterator;
    using const_iterator = typename storage_traits_type::const_iterator;

    using reverse_iterator = typename storage_traits_type::reverse_iterator;
    using const_reverse_iterator = typename storage_traits_type::const_reverse_iterator;

    using storage_tag = typename storage_traits_type::storage_tag;

    using self_type = fixed_matrix_engine<T, R, C>;
    using transpose_type = fixed_matrix_engine<T, C, R>;

    fixed_matrix_engine() = default;

    fixed_matrix_engine(const self_type &other) = default;

    fixed_matrix_engine(self_type &&other) noexcept = default;

    fixed_matrix_engine(std::initializer_list<std::initializer_list<value_type>> lst) {
        assert(lst.size() <= m_rows); // bound checking
        size_type max_c{0};
        for (auto &x: lst) {
            max_c = std::max(max_c, x.size());
        }
        assert(max_c <= m_cols); // bound checking
        auto it = lst.begin();
        for (size_type i{0}; i < lst.size(); i++) {
            std::copy(it->begin(), it->end(), m_data.begin() + i * m_cols);
            it++;
        }
    }

//    template<typename T2>
//    constexpr fixed_matrix_engine &operator=(fixed_matrix_engine<T2, R, C> const & other) {
//        std::copy(other.begin(), other.end(), m_data.begin());
//    }

    constexpr fixed_matrix_engine &operator=(fixed_matrix_engine &&) noexcept = default;

    constexpr fixed_matrix_engine &operator=(fixed_matrix_engine const &) = default;

    constexpr size_pair size() noexcept {
        return std::make_pair(m_cols, m_rows);
    }

    static constexpr size_type m_rows{R};
    static constexpr size_type m_cols{C};

    array_type m_data;
};

template<typename T>
struct dynamic_matrix_engine {
    using scalar_type = T;

    using array_type = std::vector<scalar_type>;
    using storage_traits_type = storage_traits<array_type>;

    using size_type = typename storage_traits_type::size_type;
    using size_pair = std::pair<size_type, size_type>;
    using difference_type = typename storage_traits_type::difference_type;

    using value_type = typename storage_traits_type::value_type;

    using reference = typename storage_traits_type::reference;
    using const_reference = typename storage_traits_type::const_reference;

    using pointer = typename storage_traits_type::pointer;
    using const_pointer = typename storage_traits_type::const_pointer;

    using iterator = typename storage_traits_type::iterator;
    using const_iterator = typename storage_traits_type::const_iterator;

    using reverse_iterator = typename storage_traits_type::reverse_iterator;
    using const_reverse_iterator = typename storage_traits_type::const_reverse_iterator;

    using storage_tag = typename storage_traits_type::storage_tag;

    using self_type = dynamic_matrix_engine<T>;
    using transpose_type = self_type;

    dynamic_matrix_engine() = default;

    dynamic_matrix_engine(const self_type &other) = default;

    dynamic_matrix_engine(self_type &&other) noexcept = default;

    dynamic_matrix_engine(size_type r, size_type c) : m_rows(r), m_cols(c), m_data(r * c) {};

    template<typename U, std::size_t R, std::size_t C>
    explicit dynamic_matrix_engine(fixed_matrix_engine<U, R, C> other) : m_rows(R), m_cols(C),
                                                                         m_data(R * C) {};

    dynamic_matrix_engine(std::initializer_list<std::initializer_list<value_type>> lst) :
            m_rows{lst.size()},
            m_cols{0} { // At this time we are not sure what the column size should be
        for (auto &x: lst) {
            m_cols = std::max(m_cols, x.size());
        }
        m_data = array_type(m_rows, m_cols);
        auto it = lst.begin();
        for (size_type i{0}; i < lst.size(); i++) {
            std::copy(it->begin(), it->end(),
                      m_data.begin() + i * m_cols); // copy current inner list
            it++;
        }
    }

    constexpr dynamic_matrix_engine &operator=(dynamic_matrix_engine &&) noexcept = default;

    constexpr dynamic_matrix_engine &operator=(dynamic_matrix_engine const &) = default;

    constexpr size_pair size() noexcept {
        return std::make_pair(m_cols, m_rows);
    }

    array_type m_data;
    size_type m_rows;
    size_type m_cols;
};

} // namespace boost::numeric::ublas::experimental

#endif // BOOST_NUMERIC_UBLAS_MATRIX_ENGINE_H
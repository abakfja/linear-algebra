//
//  Copyright (c) 2021 Kannav Mehta
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_UBLAS_VECTOR_ENGINE_H
#define BOOST_NUMERIC_UBLAS_VECTOR_ENGINE_H

#include <cstddef>
#include <array>
#include <vector>
#include <tuple>
#include <cassert>

#include <boost/numeric/ublas/matrix/traits/storage_traits.hpp>
#include <boost/numeric/ublas/matrix/traits/engine_traits.hpp>

namespace boost::numeric::ublas::experimental {

template<typename T, std::size_t N>
struct fixed_vector_engine {
    using array_type = std::array<T, N>;
    using storage_traits_type = storage_traits<array_type>;

    using size_type = typename storage_traits_type::size_type;
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

    using self_type = fixed_vector_engine<T, N>;
    using transpose_type = fixed_vector_engine<T, N>;

    ~fixed_vector_engine() noexcept = default;

    constexpr fixed_vector_engine() = default;

    constexpr fixed_vector_engine(const self_type &other) = default;

    constexpr fixed_vector_engine(self_type &&other) noexcept = default;

    // for compatibility
    constexpr explicit fixed_vector_engine(size_type sz) : m_data() {
        std::fill(m_data.begin(), m_data.end(), value_type{});
    }

    constexpr explicit fixed_vector_engine(value_type v) : m_data() {
        std::fill(m_data.begin(), m_data.end(), v);
    }

    template<typename U>
    fixed_vector_engine(std::initializer_list<U> lst) {
        assert(lst.size() <= m_elems); // bound checking
        std::copy(lst.begin(), lst.end(), m_data.begin());
    }

    constexpr fixed_vector_engine &operator=(fixed_vector_engine &&) noexcept = default;

    constexpr fixed_vector_engine &operator=(fixed_vector_engine const &) = default;

    constexpr reference operator[](size_type idx) {
        return m_data[idx]; // no bound checking here
    }

    constexpr const_reference operator[](size_type idx) const {
        return m_data[idx]; // no bound checking here
    }

    [[nodiscard]] constexpr size_type size() const {
        return m_data.size();
    }

    [[nodiscard]] constexpr bool empty() const {
        return m_data.empty();
    }

    constexpr auto begin() noexcept {
        return m_data.begin();
    }

    constexpr auto end() noexcept {
        return m_data.end();
    }

    constexpr auto begin() const noexcept {
        return m_data.begin();
    }

    constexpr auto end() const noexcept {
        return m_data.end();
    }

    static constexpr size_type m_elems{N};

    array_type m_data;
};

template<typename T>
struct dynamic_vector_engine {
    using scalar_type = T;

    using array_type = std::vector<scalar_type>;
    using storage_traits_type = storage_traits<array_type>;

    using size_type = typename storage_traits_type::size_type;
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

    using self_type = dynamic_vector_engine<T>;
    using transpose_type = self_type;

    ~dynamic_vector_engine() noexcept = default;

    dynamic_vector_engine() = default;

    dynamic_vector_engine(const self_type &other) = default;

    dynamic_vector_engine(self_type &&other) noexcept = default;

    explicit dynamic_vector_engine(size_type n, value_type v = {}) : m_elems{n}, m_data(m_elems, v) {
    };

    template<typename U, std::size_t N>
    explicit
    dynamic_vector_engine(fixed_vector_engine<U, N> other) : m_elems{N}, m_data(m_elems) {};

    template<typename U>
    dynamic_vector_engine(std::initializer_list<U> lst) : m_elems{lst.size()},
                                                          m_data(m_elems) {
        std::copy(lst.begin(), lst.end(), m_data.begin());
    }

    constexpr dynamic_vector_engine &operator=(dynamic_vector_engine &&) noexcept = default;

    constexpr dynamic_vector_engine &operator=(dynamic_vector_engine const &) = default;

    reference operator[](size_type idx) {
        return m_data[idx]; // no bound checking here
    }

    const_reference operator[](size_type idx) const {
        return m_data[idx]; // no bound checking here
    }

    [[nodiscard]] constexpr size_type size() const {
        return m_data.size();
    }

    [[nodiscard]] constexpr bool empty() const {
        return m_data.empty();
    }

    constexpr auto begin() noexcept {
        return m_data.begin();
    }

    constexpr auto end() noexcept {
        return m_data.end();
    }

    constexpr auto begin() const noexcept {
        return m_data.begin();
    }

    constexpr auto end() const noexcept {
        return m_data.end();
    }

    size_type m_elems;
    array_type m_data;
};

} // namespace boost::numeric::ublas::experimental

namespace boost::numeric::ublas::experimental::detail {
template<typename T, std::size_t N>
struct is_static<fixed_vector_engine<T, N>> : std::true_type {
};

template<typename T>
struct is_dynamic<dynamic_vector_engine<T>> : std::true_type {
};

} // namespace boost::numeric::ublas::experimental::detail

#endif // BOOST_NUMERIC_UBLAS_VECTOR_ENGINE_H
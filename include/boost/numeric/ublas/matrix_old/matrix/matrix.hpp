//
// Created by fragrant on 3/28/21.
//

#ifndef UBLAS_MATRIX_HPP
#define UBLAS_MATRIX_HPP

#include <boost/numeric/ublas/matrix/matrix/matrix_engine.hpp>
#include <boost/numeric/ublas/matrix/matrix/traits/engine_traits.hpp>
#include <boost/numeric/ublas/matrix/matrix/traits/matrix_traits.hpp>

namespace boost::numeric::ublas::experimental {

template<class engine>
class matrix {
public:
    using scalar_type = typename engine::scalar_type;
    using scalar_reference = scalar_type &;
    using scalar_const_reference = const scalar_type &;

    using storage_traits_type = typename engine::storage_traits_type;

    using storage_type = typename storage_traits_type::storage_type;

    using size_type = typename storage_traits_type::size_type;
    using index_type = std::pair<size_type, size_type>;
    using difference_type = typename storage_traits_type::difference_type;

    using reference = typename storage_traits_type::reference;
    using const_reference = typename storage_traits_type::const_reference;

    using pointer = typename storage_traits_type::pointer;
    using const_pointer = typename storage_traits_type::const_pointer;

    using iterator = typename storage_traits_type::iterator;
    using const_iterator = typename storage_traits_type::const_iterator;

    using reverse_iterator = typename storage_traits_type::reverse_iterator;
    using const_reverse_iterator = typename storage_traits_type::const_reverse_iterator;

    using resizable_tag = typename storage_traits_type::resizable_tag;


    template<typename E = engine,
            typename = detail::enable_if_static<E>>
    matrix(std::initializer_list<scalar_type> l): matrix(resizable_tag{}) {
        std::copy(l.begin(), l.end(), m_data.begin());
    }

    template<typename E = engine,
            typename = detail::enable_if_static<E>>
    explicit matrix(scalar_const_reference v): matrix(resizable_tag{}) {
        fill(v);
    }

    template<typename E = engine,
            typename = detail::enable_if_dynamic<E>>
    explicit matrix(
            size_type r,
            size_type c,
            std::initializer_list<scalar_type> l
    ) : matrix(r, c, resizable_tag{}) {
        std::copy(l.begin(), l.end(), m_data.begin());
    }

    template<typename E = engine,
            typename = detail::enable_if_dynamic<E>>
    constexpr explicit
    matrix(size_type r, size_type c) :
            matrix(r, c, resizable_tag{}) {
    }

    template<typename E = engine,
            typename = detail::enable_if_dynamic<E>>
    constexpr explicit
    matrix(size_type r, size_type c, scalar_type v) :
            matrix(r, c, resizable_tag{}) {
        fill(v);
    }

    [[nodiscard]] index_type size() const {
        return std::make_pair(this->rows, this->cols);
    }

    [[nodiscard]] bool empty() const {
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

    constexpr auto at(size_type pos) const {
        return m_data.at(pos);
    }

    constexpr auto at(size_type pos) {
        return m_data.at(pos);
    }

    void fill(const_reference value) {
        std::fill(begin(), end(), value);
    }

    constexpr const_reference operator[](size_type i) const {
        return this->m_data[i];
    }

    constexpr reference operator[](size_type i) {
        return this->m_data[i];
    }

private:

    constexpr explicit matrix(size_type r,
                              size_type c,
                              storage_resizable_container_tag t
    ) : rows{r}, cols{c}, m_data(rows * cols) {
    }

    constexpr explicit matrix(storage_static_container_tag t) :
            rows{engine::rows}, cols{engine::cols} {
    }

    size_type rows;
    size_type cols;
    storage_type m_data;
};

}
#endif //UBLAS_MATRIX_HPP

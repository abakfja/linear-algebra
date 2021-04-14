//
// Created by fragrant on 4/9/21.
//

#ifndef UBLAS_HELPER_HPP
#define UBLAS_HELPER_HPP

#include <initializer_list>
#include <stdexcept>

namespace boost::numeric::ublas::experimental::detail {

template<class Engine, class size_type>
inline constexpr void check_engine_size(Engine const &engine, size_type n_elem) {
    if (engine.size() != n_elem) {
        throw std::runtime_error(
                "source vector size does not match destination vector size");
    }
}

template<class Engine, class size_type>
inline constexpr void check_engine_size(Engine const &engine, size_type rows, size_type cols) {
    if (engine.rows() != rows || engine.cols() != cols) {
        throw std::runtime_error(
                "source matrix size does not match destination matrix size");
    }
}

template<class T, class size_type>
inline constexpr void check_init_list(std::initializer_list<T> list, size_type elems) {
    if (list.size() != static_cast<size_t>(elems)) {
        throw std::runtime_error("initializer_list size does not match vector size");
    }
}

template<class T>
inline constexpr void check_init_list(std::initializer_list<std::initializer_list<T>> list) {
    size_t first_row_size = list.begin()->size();
    for (auto const row : list) {
        if (row.size() != first_row_size) {
            throw std::runtime_error("source 2-D initializer_list has invalid shape");
        }
    }
}

template<class T, class size_type>
inline constexpr void
check_init_list(std::initializer_list<std::initializer_list<T>> list, size_type rows,
                size_type cols) {
    size_t first_row_size = list.begin()->size();
    for (auto const row : list) {
        if (row.size() != first_row_size) {
            throw std::runtime_error("source 2-D initializer_list has invalid shape");
        }
    }
    if (list.size() != static_cast<size_t>(rows) || first_row_size != static_cast<size_t>(cols)) {
        throw std::runtime_error("source 2-D initializer_list size does not match "
                                 "destination matrix engine size");
    }
}


} // namespace boost::numeric::ublas::experimental::detail


namespace boost::numeric::ublas::experimental::detail {

template<class Engine1, class Engine2>
inline constexpr void
copy_matrix_engine(Engine1 &dest, const Engine2 &src) {
    using value_type = typename Engine1::value_type;
    using size_type = typename Engine1::size_type;

    for (size_type i{}; i < dest.rows(); i++) {
        for (size_type j{}; j < dest.cols(); j++) {
            dest(i, j) = static_cast<value_type>(src(i, j));
        }
    }
}


template<class Engine1, typename T>
inline constexpr void
copy_matrix_engine(Engine1 &dest, const std::initializer_list<std::initializer_list<T>> &src) {
    using value_type = typename Engine1::value_type;
    using size_type = typename Engine1::size_type;
    auto it = src.begin();
    for (size_type i{}; i < dest.rows(); i++) {

        auto it2 = it->begin();

        for (size_type j{}; j < dest.cols(); j++) {
            dest(i, j) = static_cast<value_type>(*it2);
            it2++;
        }
        it++;
    }
}


template<class Engine1, class Engine2>
inline constexpr void
copy_vector_engine(Engine1 &dest, const Engine2 &src) {
    using value_type = typename Engine1::value_type;
    using size_type = typename Engine1::size_type;

    for (size_type i{}; i < dest.size(); i++) {
        dest[i] = static_cast<value_type>(src[i]);
    }
}


template<class Engine1, typename T>
inline constexpr void
copy_vector_engine(Engine1 &dest, const std::initializer_list<T> &src) {
    using value_type = typename Engine1::value_type;
    using size_type = typename Engine1::size_type;
    auto it = src.begin();
    for (size_type i{}; i < dest.size(); i++) {
        dest[i] = static_cast<value_type>(*(it++));
    }
}

}
#endif //UBLAS_HELPER_HPP

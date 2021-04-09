//
// Created by fragrant on 4/9/21.
//

#ifndef UBLAS_HELPER_HPP
#define UBLAS_HELPER_HPP

#include <initializer_list>
#include <exception>

namespace boost::numeric::ublas::experimental {

template<class Engine, class ST>
inline constexpr void check_engine_size(Engine const &engine, ST n_elem) {
    if (engine.size() != n_elem) {
        throw std::runtime_error(
                "source engine size does not match destination vector engine size");
    }
}

template<class Engine, class ST>
inline constexpr void check_engine_size(Engine const &engine, ST rows, ST cols) {
    if (engine.rows() != rows || engine.columns() != cols) {
        throw std::runtime_error(
                "source engine size does not match destination matrix engine size");
    }
}

template<class T, class ST>
inline constexpr void check_init_list(std::initializer_list<T> list, ST elems) {
    if (list.size() != static_cast<size_t>(elems)) {
        throw std::runtime_error("initializer_list size does not match vector engine size");
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

template<class T, class ST>
inline constexpr void
check_init_list(std::initializer_list<std::initializer_list<T>> list, ST rows, ST cols) {
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


} // namespace boost::numeric::ublas::experimental

#endif //UBLAS_HELPER_HPP

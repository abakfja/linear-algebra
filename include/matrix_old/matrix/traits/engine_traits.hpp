//
// Created by abakfja on 3/29/21.
//

#ifndef UBLAS_MATRIX_ENGINE_TRAITS_HPP
#define UBLAS_MATRIX_ENGINE_TRAITS_HPP

#include <boost/numeric/ublas/matrix/engine_traits.hpp>

namespace boost::numeric::ublas::experimental {

template<typename T, std::size_t R, std::size_t C>
struct static_matrix_engine;

template<typename T>
struct dynamic_matrix_engine;

} // namespace boost::numeric::ublas::experimental

namespace boost::numeric::ublas::experimental::detail {
template<typename T, std::size_t R, std::size_t C>
struct is_static<static_matrix_engine<T, R, C>> : std::true_type {
};

template<typename T>
struct is_dynamic<dynamic_matrix_engine<T>> : std::true_type {
};

}

#endif //UBLAS_MATRIX_ENGINE_TRAITS_HPP

//
//  Copyright (c) 2021 Kannav Mehta
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UBLAS_MATRIX_TRAIT_H
#define UBLAS_MATRIX_TRAIT_H

#include <boost/numeric/ublas/matrix/engine_traits.hpp>

namespace boost::numeric::ublas::experimental {
template<typename T>
class matrix;
} // namespace boost::numeric::ublas::experimental

namespace boost::numeric::ublas::experimental::detail {

/// @brief checks if type is a matrix
template<typename T>
struct is_matrix : std::false_type {
};

template<typename T>
struct is_matrix<matrix<T>> : std::true_type {
};

template<typename T>
using is_matrix_t = typename is_matrix<std::decay_t<T>>::type;

template<typename T>
inline constexpr bool is_matrix_v = is_matrix_t<T>::value;

template<typename T>
struct is_matrix<T &> : is_matrix<T> {
};

/// @brief used for type space reduction in expression templates
template<typename T>
using enable_if_matrix = std::enable_if_t<is_matrix_v<T>>;

} // namespace boost::numeric::ublas::experimental::detail


namespace boost::numeric::ublas::experimental {

template <typename E>
struct matrix_traits;

template<typename E>
struct matrix_traits<matrix<E>>;

template<typename E, detail::enable_if_dynamic<E>>
struct matrix_traits<matrix<E>> {

};
}

#endif //UBLAS_MATRIX_TRAIT_H

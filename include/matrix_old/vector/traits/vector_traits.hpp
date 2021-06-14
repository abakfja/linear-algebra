//
//  Copyright (c) 2021 Kannav Mehta
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef LA_VECTOR_TRAITS_HPP
#define LA_VECTOR_TRAITS_HPP

namespace boost::numeric::ublas::experimental {
template<typename T>
class row_vector;

class column_vector;
} // namespace boost::numeric::ublas::experimental

namespace boost::numeric::ublas::experimental::detail {

/// @brief checks if type is a column_vector
template<typename T>
struct is_column_vector : std::false_type {
};

template<typename T>
struct is_column_vector<column_vector<T>> : std::true_type {
};

template<typename T>
using is_column_vector_t = typename is_column_vector<std::decay_t < T>>::type;

template<typename T>
inline constexpr bool is_column_vector_v = is_column_vector_t<T>::value;

template<typename T>
struct is_column_vector<T &> : is_column_vector<T> {
};

/// @brief used for type space reduction in expression templates
template<typename T>
using enable_if_column_vector = std::enable_if_t<is_column_vector_v<T>>;

/// @brief checks if type is a row_vector
template<typename T>
struct is_row_vector : std::false_type {
};

template<typename T>
struct is_row_vector<row_vector<T>> : std::true_type {
};

template<typename T>
using is_row_vector_t = typename is_row_vector<std::decay_t < T>>::type;

template<typename T>
inline constexpr bool is_row_vector_v = is_row_vector_t<T>::value;

template<typename T>
struct is_row_vector<T &> : is_row_vector<T> {
};

/// @brief used for type space reduction in expression templates
template<typename T>
using enable_if_row_vector = std::enable_if_t<is_row_vector_v<T>>;

} // namespace boost::numeric::ublas::experimental::traits

#endif //LA_VECTOR_TRAITS_HPP

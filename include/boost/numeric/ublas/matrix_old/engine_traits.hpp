//
// Created by fragrant on 3/28/21.
//

#ifndef UBLAS_ENGINE_TRAITS_HPP
#define UBLAS_ENGINE_TRAITS_HPP


namespace boost::numeric::ublas::experimental::detail {

/// @brief checks if type is a matrix_old
template<typename T>
struct is_static : std::false_type {
};

template<typename T>
using is_static_t = typename is_static<std::decay_t<T>>::type;

template<typename T>
inline constexpr bool is_static_v = is_static_t<T>::value;

template<typename T>
struct is_static<T &> : is_static<T> {
};

/// @brief used for type space reduction in expression templates
template<typename T>
using enable_if_static = std::enable_if_t<is_static_v<T>>;



/// @brief checks if type is a matrix_old
template<typename T>
struct is_dynamic : std::false_type {
};

template<typename T>
using is_dynamic_t = typename is_dynamic<std::decay_t<T>>::type;

template<typename T>
inline constexpr bool is_dynamic_v = is_dynamic_t<T>::value;

template<typename T>
struct is_dynamic<T &> : is_dynamic<T> {
};

/// @brief used for type space reduction in expression templates
template<typename T>
using enable_if_dynamic = std::enable_if_t<is_dynamic_v<T>>;


} // namespace boost::numeric::ublas::experimental::engine

#endif //UBLAS_ENGINE_TRAITS_HPP

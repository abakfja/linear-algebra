//
// Created by abakfja on 3/29/21.
//

#ifndef LA_VECTOR_ENGINE_TRAITS_HPP
#define LA_VECTOR_ENGINE_TRAITS_HPP

#include <boost/numeric/ublas/matrix/engine_traits.hpp>

namespace boost::numeric::ublas::experimental {

template<typename T, std::size_t N, class Layout>
struct static_vector_engine;

template<typename T, class layout_tag>
struct dynamic_vector_engine;

} // namespace boost::numeric::ublas::experimental

namespace boost::numeric::ublas::experimental::detail {
template<typename T, std::size_t N, class Layout>
struct is_static<static_vector_engine<T, N, Layout>> : std::true_type {
};

template<typename T, class Layout>
struct is_dynamic<dynamic_vector_engine<T, Layout>> : std::true_type {
};

}

#endif //LA_ENGINE_TRAITS_HPP

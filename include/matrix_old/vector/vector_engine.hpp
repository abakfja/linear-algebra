//
// Created by abakfja on 3/28/21.
//

#ifndef LA_VECTOR_ENGINE_HPP
#define LA_VECTOR_ENGINE_HPP


#include <boost/numeric/ublas/matrix/storage_traits.hpp>

namespace boost::numeric::ublas::experimental::layout {
    struct row_major{};
    struct column_major{};
}

namespace boost::numeric::ublas::experimental {

template<typename T, std::size_t N, class Layout>
struct static_vector_engine {
    using scalar_type = T;
    using array_type = std::array<scalar_type, N>;
    using storage_traits_type = storage_traits<array_type>;
    using size_type = typename storage_traits_type::size_type;
    using resizable_tag = typename storage_traits_type::resizable_tag;
    using layout_tag = Layout;
    static constexpr size_type n = N;
};

template<typename T, class Layout>
struct dynamic_vector_engine {
    using scalar_type = T;
    using array_type = std::vector<T>;
    using storage_traits_type = storage_traits<array_type>;
    using resizable_tag = typename storage_traits_type::resizable_tag;
    using layout_tag = Layout;
};

}

#endif //LA_VECTOR_ENGINE_HPP

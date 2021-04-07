//
// Created by fragrant on 3/28/21.
//

#ifndef UBLAS_MATRIX_ENGINE_HPP
#define UBLAS_MATRIX_ENGINE_HPP

#include <boost/numeric/ublas/matrix/storage_traits.hpp>
#include <cstddef>

namespace boost::numeric::ublas::experimental {

template<typename T, std::size_t R, std::size_t C>
struct static_matrix_engine {
    using scalar_type = T;
    using array_type = std::array<scalar_type, R * C>;
    using storage_traits_type = storage_traits<array_type>;
    using size_type = typename storage_traits_type::size_type;
    using resizable_tag = typename storage_traits_type::resizable_tag;
    static constexpr size_type rows = R;
    static constexpr size_type cols = C;
};

template<typename T>
struct dynamic_matrix_engine {
    using scalar_type = T;
    using array_type = std::vector<T>;
    using storage_traits_type = storage_traits<array_type>;
    using resizable_tag = typename storage_traits_type::resizable_tag;
};

}

#endif //UBLAS_MATRIX_ENGINE_HPP

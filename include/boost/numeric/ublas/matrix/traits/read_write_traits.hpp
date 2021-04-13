//
// Created by fragrant on 4/9/21.
//

#ifndef UBLAS_READ_WRITE_TRAITS_H
#define UBLAS_READ_WRITE_TRAITS_H

#include <boost/numeric/ublas/matrix/detail/tags.hpp>

namespace boost::numeric::ublas::experimental {

template<typename Engine, typename VT>
struct read_write_traits;

template<typename Engine>
struct read_write_traits<Engine, detail::read_only_view_tag> {
    using reference = typename Engine::const_reference;
    using pointer = typename Engine::const_pointer;
    using engine_reference = const std::remove_cv_t<Engine>;
};


template<typename Engine>
struct read_write_traits<Engine, detail::read_write_view_tag> {
    using reference = typename Engine::reference;
    using pointer = typename Engine::pointer;
    using engine_reference = std::remove_cv_t<Engine>;

};

}

#endif //UBLAS_READ_WRITE_TRAITS_H

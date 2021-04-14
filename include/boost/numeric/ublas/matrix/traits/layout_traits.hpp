//
// Created by abakfja on 4/4/21.
//

#ifndef UBLAS_LAYOUT_TRAITS_HPP
#define UBLAS_LAYOUT_TRAITS_HPP

namespace boost::numeric::ublas::experimental::layout {

struct column_major;
struct row_major;

struct column_major {
    using transpose_type = row_major;
};

struct row_major {
    using transpose_type = column_major;
};

};

#endif //UBLAS_LAYOUT_TRAITS_HPP

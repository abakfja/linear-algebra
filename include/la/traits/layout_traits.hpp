//
// Created by abakfja on 4/4/21.
//

#ifndef LA_LAYOUT_TRAITS_HPP
#define LA_LAYOUT_TRAITS_HPP

namespace la::layout {

struct column_major;
struct row_major;

struct column_major {
    using transpose_type = row_major;
};

struct row_major {
    using transpose_type = column_major;
};

};

#endif //LA_LAYOUT_TRAITS_HPP

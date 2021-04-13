//
//  Copyright (c) 2021 Kannav Mehta
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_UBLAS_MATRIX_TAGS_H
#define BOOST_NUMERIC_UBLAS_MATRIX_TAGS_H

namespace boost::numeric::ublas::experimental::detail {

struct storage_dynamic_container_tag{};
struct storage_static_container_tag{};

/**
 * These tags signify the nature of the view engines
 */
struct read_only_view_tag{};
struct read_write_view_tag{};

/**
 * This tag is for calling the inner-constructors of matrix and vector engines
 */
struct constructor_tag{};

} // namespace boost::numeric::ublas::experimental


#endif // BOOST_NUMERIC_UBLAS_MATRIX_TAGS_H
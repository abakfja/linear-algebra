
//  Copyright (c) 2021 Kannav Mehta
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef LA_DYNAMIC_MATRIX_HPP
#define LA_DYNAMIC_MATRIX_HPP

#include <memory>
#include <tuple>
#include <iostream>

namespace boost::numeric::ublas::experimental {

/**
 * A dynamic_matrix class for a run time size dynamic_matrix
 * @tparam T: The scalar type of the dynamic_matrix
 */
template<typename T>
class dynamic_matrix {
public:
    static_assert(std::is_same<typename std::remove_cv<T>::type, T>::value,
                  "dynamic_matrix must have a non-const, non-volatile scalar_type");
    using scalar_t = T;
    using scalar_ref = T &;
    using size_type = std::pair<std::size_t, std::size_t>;
    using matrix_t = dynamic_matrix<T>;

    // Default constructor
    dynamic_matrix() = default;

    // Copy constructor
    dynamic_matrix(const dynamic_matrix::matrix_t &p) :
            r{p.r}, c{p.c},
            storage(new scalar_t[r * c]) {
        std::copy(p.storage.get(), p.storage.get() + p.r * p.c, storage.get());
    }

    // Constructor for dynamic_matrix of definitive size
    explicit dynamic_matrix(const size_type &size) :
            r{size.first},
            c{size.second},
            storage(storage(new scalar_t[r * c])) {}

    [[nodiscard]] size_type size() const {
        return std::make_pair(r, c);
    }

    [[nodiscard]] bool empty() const {
        return r * c == 0;
    }

    // Why a c style array over std::initializer_list
    // std::initializer list size is not available at compile time This would
    // not guarantee that all the row of the dynamic_matrix are of equal width.
    // However this guarantees that all of the row sizes are equal
    // and this is about 3.5 times faster(measured on gcc-9.2 -O2)
    template<std::size_t N, std::size_t M>
    explicit
    dynamic_matrix(const dynamic_matrix::scalar_t(&list)[N][M]):
            r{N},
            c{M},
            storage(new scalar_t[r * c]) {
        for (std::size_t i = 0; i < N; i++) {
            std::copy(list[i], list[i] + c, storage.get() + i * c);
        }
    }

    scalar_t operator()(size_t i, size_t j) const {
        return storage.get()[i * c + j];
    }

    scalar_ref operator()(size_t i, size_t j) {
        return storage.get()[i * c + j];
    }

private:
    std::size_t r{};
    std::size_t c{};
    std::unique_ptr<scalar_t[]> storage = nullptr;
};

} // namespace boost::numeric::ublas::experimental
#endif
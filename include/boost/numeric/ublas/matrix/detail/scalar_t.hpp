#ifndef BOOST_UBLAS_MATRIX_DETAIL_SCALAR_HPP
#define BOOST_UBLAS_MATRIX_DETAIL_SCALAR_HPP

namespace boost::numeric::ublas::experimental::detail {

template <typename T>
struct scalar_t {
    const T& s;

    constexpr explicit scalar_t(const T& v) : s(v) {}

    constexpr const T& operator[](std::size_t) const {
        return s;
    }

    [[nodiscard]] constexpr std::size_t size() const {
        return 0UL;
    }
};

}  // namespace boost::numeric::ublas::experimental::detail

#endif  // BOOST_UBLAS_MATRIX_DETAIL_SCALAR_HPP

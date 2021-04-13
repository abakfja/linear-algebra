//
// Created by fragrant on 4/13/21.
//

#ifndef UBLAS_SLICE_HPP
#define UBLAS_SLICE_HPP

namespace boost::numeric::ublas::experimental {
template<typename T = std::size_t>
struct splice {

    splice() = delete;

    constexpr splice(T start, T end) : m_start{start}, m_elems{end - start} {
        if (start > end) {
            m_elems = 0;
        }
    }

    constexpr splice(const splice &) = default;

    constexpr splice(splice &&) noexcept = default;

    bool operator==(const splice &rhs) const {
        return std::tie(m_start, m_elems) == std::tie(rhs.m_start, rhs.m_elems);
    }

    bool operator!=(const splice &rhs) const {
        return !(rhs == *this);
    }

    constexpr T size() noexcept {
        return m_elems;
    }

    constexpr T end() noexcept {
        return m_start + m_elems;
    }

    constexpr T start() noexcept {
        return m_start;
    }

    T m_start;
    T m_elems;
};
}

#endif //UBLAS_SLICE_HPP

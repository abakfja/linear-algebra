//
// Created by abakfja on 4/13/21.
//

#ifndef UBLAS_SLICE_HPP
#define UBLAS_SLICE_HPP

namespace boost::numeric::ublas::experimental {
template<typename T = std::size_t>
struct slice {

    slice() = delete;

    constexpr slice(T start, T end) : m_start{start}, m_elems{end - start} {
        if (start > end) {
            m_elems = 0;
        }
    }

    constexpr slice(const slice &) = default;

    constexpr slice(slice &&) noexcept = default;

    bool operator==(const slice &rhs) const {
        return std::tie(m_start, m_elems) == std::tie(rhs.m_start, rhs.m_elems);
    }

    bool operator!=(const slice &rhs) const {
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

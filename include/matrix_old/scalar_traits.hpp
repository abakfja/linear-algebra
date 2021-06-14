//
// Created by abakfja on 4/2/21.
//

#ifndef LA_SCALAR_TRAITS_HPP
#define LA_SCALAR_TRAITS_HPP

template<typename T>
struct scalar_value_traits : detail::compare_traits<std::decay_t < T>> {
    using value_type = std::decay_t<T>;
    using type = value_type;
    using value_tag = tag::scalar;
    using lvalue_reference = std::add_lvalue_reference_t<value_type>;
    using const_reference = std::add_lvalue_reference_t <std::add_const_t<value_type>>;

    using pointer = std::add_pointer_t<T>;
    using const_pointer = std::add_pointer_t<T const>;

    using magnitude_traits = detail::magnitude_traits_impl<T, std::is_integral<value_type>::value>;
    using magnitude_type = typename magnitude_traits::magnitude_type;
};

#endif //LA_SCALAR_TRAITS_HPP

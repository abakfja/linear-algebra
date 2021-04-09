//
// Created by abakfja on 4/4/21.
//

#ifndef UBLAS_EXPRESSION_TRAITS_HPP
#define UBLAS_EXPRESSION_TRAITS_HPP

#include <type_traits>

namespace boost::numeric::ublas::experimental {

template<class Engine, class Layout>
class vector;

template<typename operation, typename ... operands>
class vector_expr;

}  // namespace boost::numeric::ublas::experimental

namespace boost::numeric::ublas::experimental::detail {

template<class LHS, class RHS>
struct bin_vec_op_ok : std::false_type {
};

template<class Engine1, class Layout1, class Engine2>  // only vectors with same layout will add
struct bin_vec_op_ok<vector<Engine1, Layout1>, vector<Engine2, Layout1>> : std::true_type {
};

template<typename T, class Engine, class Layout>
struct bin_vec_op_ok<T, vector<Engine, Layout>> : std::true_type {
};

template<typename T, class Engine, class Layout>
struct bin_vec_op_ok<vector<Engine, Layout>, T> : std::true_type {
};

template<typename LHS, typename RHS>
using bin_vec_op_ok_t = typename bin_vec_op_ok<std::decay_t<LHS>,
        std::decay_t<RHS>>::type;

template<typename LHS, typename RHS>
inline constexpr bool is_bin_vec_op_ok = bin_vec_op_ok_t<LHS, RHS>::value;

}  // namespace boost::numeric::ublas::experimental::detail

namespace boost::numeric::ublas::experimental::detail {

template<typename T>
struct is_vector_or_expr : std::false_type {
};

template<class Engine, class Layout>
struct is_vector_or_expr<vector<Engine, Layout>> : std::true_type {
};

template<typename operation, typename ... operands>
struct is_vector_or_expr<vector_expr<operation, operands...>> : std::true_type {
};

template<typename T>
using is_vector_or_expr_t = typename is_vector_or_expr<std::decay<T>>::type;

template<typename T>
inline constexpr bool is_vector_or_expr_v = is_vector_or_expr<T>::value;

}  // namespace boost::numeric::ublas::experimental::detail

#endif  //UBLAS_EXPRESSION_TRAITS_HPP

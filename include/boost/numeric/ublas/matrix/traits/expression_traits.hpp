//
// Created by abakfja on 4/4/21.
//

#ifndef UBLAS_EXPRESSION_TRAITS_HPP
#define UBLAS_EXPRESSION_TRAITS_HPP

#include <type_traits>

namespace boost::numeric::ublas::experimental {

template<class Engine, class Layout>
class vector;

template<typename E>
struct base_vector_expression;

template<typename operation, typename ... operands>
struct vector_expression;

}  // namespace boost::numeric::ublas::experimental


namespace boost::numeric::ublas::experimental::detail {

template<typename T>
struct is_vector_expr : std::false_type {
};

template<class Engine, class Layout>
struct is_vector_expr<vector<Engine, Layout>> : std::true_type {
};

template<typename E>
struct is_vector_expr<base_vector_expression<E>> : std::true_type {
};

template<typename operation, typename ... operands>
struct is_vector_expr<vector_expression<operation, operands...>> : std::true_type {
};

template<typename T>
using is_vector_expr_t = typename is_vector_expr<std::decay<T>>::type;

template<typename T>
inline constexpr bool is_vector_expr_v = is_vector_expr<T>::value;

}  // namespace boost::numeric::ublas::experimental::detail


namespace boost::numeric::ublas::experimental {

template<class Engine>
class matrix;

template<typename E>
struct base_matrix_expression;

template<class operation, typename ... operands>
struct matrix_expression;

template<class T>
struct transpose_expression;

}  // namespace boost::numeric::ublas::experimental

namespace boost::numeric::ublas::experimental::detail {

template<class LHS, class RHS>
struct bin_mat_op_ok : std::false_type {
};

template<class Engine1, class Engine2>  // only matrices with same layout will add
struct bin_mat_op_ok<matrix<Engine1>, matrix<Engine2>> : std::true_type {
};

template<typename T, class Engine>
struct bin_mat_op_ok<T, matrix<Engine>> : std::true_type {
};

template<typename T, class Engine>
struct bin_mat_op_ok<matrix<Engine>, T> : std::true_type {
};

template<typename LHS, typename RHS>
using bin_mat_op_ok_t = typename bin_mat_op_ok<std::decay_t<LHS>,
        std::decay_t<RHS>>::type;

template<typename LHS, typename RHS>
inline constexpr bool is_bin_mat_op_ok = bin_mat_op_ok_t<LHS, RHS>::value;

}  // namespace boost::numeric::ublas::experimental::detail

namespace boost::numeric::ublas::experimental::detail {

template<typename T>
struct is_matrix_expr : std::false_type {
};

template<typename E>
struct is_matrix_expr<base_matrix_expression<E>> : std::true_type {
};


template<class OP, typename ... operands>
struct is_matrix_expr<matrix_expression<OP, operands...>> : std::true_type {
};

template<typename E>
struct is_matrix_expr<matrix<E>>: std::true_type  {
};

template<typename T>
using is_matrix_expr_t = typename is_matrix_expr<std::decay<T>>::type;

template<typename T>
inline constexpr bool is_matrix_expr_v = is_matrix_expr<T>::value;

}  // namespace boost::numeric::ublas::experimental::detail

#endif  //UBLAS_EXPRESSION_TRAITS_HPP

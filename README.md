```c++
matrix<matrix_engine<static_matrix_engine<int, N, M>, layout::column_major>>
vector<vector_engine<fixed_size_vector<int, N>, layout::column_major>>
matrix<matrix_engine<dynamic_matrix_engine<int>, layout::column_major>>
vector<vector_engine<dynamic_size_vector<int>, layout::column_major>>
```

```c++
template<typname V, class Layout = layout::column_major>
using dynamic_matrix = matrix<matrix_engine<dynamic_matrix_engine<V>, layout>

```
```c++
matrix<matrix_engine<fixed_size_matrix<int, N, M>, layout::column_major>>
vector<vector_engine<fixed_size_vector<int, N>, layout::column_major>>
matrix<matrix_engine<dynamic_size_matrix<int>, layout::column_major>>
vector<vector_engine<dynamic_size_vector<int>, layout::column_major>>
```

```c++
template<typname T, class Layout = layout::column_major>
using dynamic_matrix = matrix<matrix_engine<dynamic_size_matrix<T>, layout>

```
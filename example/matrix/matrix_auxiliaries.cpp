//
// Created by fragrant on 3/21/21.
//

// Type your code here, or load an example.
#include <type_traits>
#include <iostream>
#include <array>

struct row_layout {
};
struct column_layout {
};

template<class T>
struct is_row_layout : std::false_type {
};

template<>
struct is_row_layout<row_layout> : std::true_type {
};

template<class T>
inline constexpr bool is_row_layout_v = is_row_layout<T>::value;


template<typename T, size_t N>
struct storage {
    using storage_type = T[N];
};

template<class T, std::size_t N, std::size_t M, class layout>
struct fixed_vector {
    using storage_type = typename storage<T, N * M>::storage_type;

    T operator()(std::size_t i, std::size_t j) {
        return data[i * M + j];
    }

    template<std::size_t A, std::size_t B>
    explicit fixed_vector(const T(&list)[A][B]) {
        static_assert(A == N && B == M);
        for (std::size_t i = 0; i < N; i++) {
            std::copy(list[i], list[i] + c, data + i * c);
        }
    }

    storage_type data;
private:
    const std::size_t r = N;
    const std::size_t c = M;
};

int main() {
    fixed_vector<int, 3, 2, row_layout> a({
                                                  {1, 2},
                                                  {3, 2},
                                                  {5, 4}
                                          });
    std::array<int, 3> ax{1, 2, 9};
    ax[2] = 1;
    auto p = a(1, 0);
    auto r = ax[2];
    std::cout << p << " " << " " << r << std::endl;
}

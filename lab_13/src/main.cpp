#include "my_array.h"

template <typename T>
void my_test() {
    my_array<T, 10> a;
    a[0] = T();
    a.fill(a[0]);
    assert(!a.empty());
    assert(a.size() == 10);
}
template <typename T>
T get_object(int i) {
    return T();
}
template <typename T, std::size_t N>
void at_function_test() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    for (size_t i = 0; i < N / 2; i++) {
        a[i] = get_object<T>(i);
    }
    for (size_t i = N / 2; i < N; i++) {
        a.at(i) = get_object<T>(i);
    }
    for (size_t i = 0; i < N; i++) {
        assert(a[i] == get_object<T>(i));
        assert(a.at(i) == get_object<T>(i));
        assert(ca[i] == get_object<T>(i));
        assert(ca.at(i) == get_object<T>(i));
    }
}
int main() {
    my_test<int>();
    at_function_test<int, 5>();
}

#include <cstddef>
#include <iostream>
#include <cassert>
#include <cstring>
#include <algorithm>
template <class T>
class my_vector{
public:
    my_vector();
    my_vector(size_t n);
    my_vector(const my_vector& other);
    my_vector& operator=(const my_vector& other);
    ~my_vector();

    size_t size() const { return _size;}
    size_t capacity() const { return _capacity;}
    bool empty() const { return _size == 0;}

    void resize(size_t n);
    void reserve(size_t n);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void push_back(const T& elem);
    void pop_back();
    void clear();

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const my_vector<U>& vector);

private:
    size_t _capacity;
    size_t _size;
    T* _array;
    void increase_capacity(size_t capacity);
    inline size_t two_power(size_t n) {
        size_t result = 1;
        while (result < n) result *= 2;
        return result;
    }
    inline void swap(my_vector& other) {
        std::swap(other._size,_size);
        std::swap(other._capacity,_capacity);
        std::swap(other._array,_array);
    }
};

template <typename T>
void my_vector<T>::increase_capacity(size_t capacity) {
    if (capacity <= _capacity) return;
    _capacity = capacity;
    T *tmp = reinterpret_cast<T*>(new char[_capacity * sizeof(T)]);
    for (size_t i = 0; i < _size; ++i) {
        new(&tmp[i]) T(_array[i]);
        _array[i].~T();
    }
    delete[] reinterpret_cast<char*>(_array);
    _array = tmp;
}



template<class T>
my_vector<T>::my_vector() {
    _size = 0, _capacity = 1;
    _array = reinterpret_cast<T*>(new char[_capacity * sizeof(T)]);
}


template<class T>
my_vector<T>::my_vector(size_t n) {
    _capacity = two_power(n);
    _size = n;
    _array = reinterpret_cast<T *>(new char[_capacity * sizeof(T)]);
    for (size_t i = 0; i < n; ++i)
        new(&_array[i]) T();
}

template<class T>
my_vector<T>::my_vector(const my_vector &other) {
    _capacity = two_power(other._size);
    _size = other._size;
    _array = reinterpret_cast<T*>(new char[_capacity * sizeof(T)]);
    for (size_t i = 0; i < _size; ++i)
        new(&_array[i]) T(other._array[i]);
}

template<class T>
my_vector<T>& my_vector<T>::operator=(const my_vector &other) {
    if (this != &other)
        my_vector(other).swap(*this);
    return *this;
}

template<class T>
my_vector<T>::~my_vector() {
    clear();
    delete[] (char*)_array;
}

template<class T>
void my_vector<T>::push_back(const T& elem) {
    if (_size == _capacity)
        increase_capacity(2 * _capacity);
    new(&_array[_size]) T(elem);
    _size++;
}

template<class T>
void my_vector<T>::pop_back() {
    assert(_size > 0);
    _size--;
    _array[_size].~T();
}

template<class T>
T &my_vector<T>::operator[](size_t index) {
    assert(_size > index);
    return _array[index];
}

template<class T>
const T& my_vector<T>::operator[](size_t index) const {
    assert(_size > index);
    return _array[index];
}

template<class T>
void my_vector<T>::resize(size_t n) {
    if (n < _size) {
        for (size_t i = n; i < _size; ++i)
            _array[i].~T();
    } else {
        increase_capacity(two_power(n));
        for (size_t i = _size; i < n; ++i)
            new(&_array[i]) T();
    }
    _size = n;
}

template<class T>
void my_vector<T>::clear() {
    while (size())
        pop_back();
}

template<class T>
void my_vector<T>::reserve(size_t n) {
    increase_capacity(two_power(n));
}


template<typename U>
std::ostream &operator<<(std::ostream &os, const my_vector<U> &vector) {
    if (vector._size == 0) return os;
    for (size_t i = 0; i < vector._size - 1; ++i) {
        os << vector[i] << ' ';
    }
    os << vector[vector._size - 1];
    return os;
}

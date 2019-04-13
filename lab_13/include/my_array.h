#include <iostream>
#include <assert.h>

template<typename T, std::size_t N>
class my_array {
public:
  const T& at(std::size_t index) const;
  T& at(std::size_t index);
  T& operator[](std::size_t index);
  const T& operator[](std::size_t index) const;

  bool empty() const;
  std::size_t size() const;

  void fill(T val);
private:
    T _data[N];
};

template<typename T, size_t N>
const  T& my_array<T, N>::at(std::size_t index) const {
    if (index < 0 || index >= N) {
        std::cerr << "Index error: " << index << " not found\n";
        assert(false);
    }
    return _data[index];
}

template<typename T, size_t N>
T &my_array<T, N>::operator[](std::size_t index) {
    return _data[index];
}


template<typename T, size_t N>
void my_array<T, N>::fill(T val) {
    for (std::size_t i = 0; i < N; ++i) {
        _data[i] = val;
    }
}


template<typename T, size_t N>
bool my_array<T, N>::empty() const {
    return false; // Если мы считаем, что N > 0, в чём смысл этой функции???
}

template<typename T, size_t N>
std::size_t my_array<T, N>::size() const {
    return N;
}

template<typename T, size_t N>
const T& my_array<T, N>::operator[](std::size_t index) const {
    return _data[index];
}

template<typename T, size_t N>
T &my_array<T, N>::at(std::size_t index) {
    if (index < 0 || index >= N) {
        std::cerr << "Index error: " << index << " not found\n";
        assert(false);
    }
    return _data[index];
}


template<std::size_t N>
class my_array<bool, N> {
private:
    class proxy{
    public:
        char* ptr;
        char index;
        proxy(char* p, char i) : ptr(p), index(i) {}
        void operator=(bool f) {
            *ptr = static_cast<char>(*ptr & (~(1 << index)));
            if (f)
                *ptr |= (1 << index);
        }
        operator bool() {
            return bool(*ptr & (1 << index));
        }
    };
    char _data[(N - 1)/8 + 1];

public:
    bool at(std::size_t index) const {
        if (index < 0 || index >= N) {
            std::cerr << "Index error: " << index << " not found\n";
            assert(false);
        }
        return bool((_data[index]) & (1 << index));
    }
    proxy operator[](std::size_t index) {
        return proxy(&(_data[index]), (char)index);
    }
    bool operator[](std::size_t index) const {
        return bool((_data[index]) & (1 << index));
    }

    bool empty() const {
        return false;
    }
    std::size_t size() const {
        return N;
    }

    void fill(bool val) {
        for (std::size_t i = 0; i < N; ++i) {
            (*this)[i] = char(val);
        }
    }

};

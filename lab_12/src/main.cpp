#include <iostream>

#include "my_vector.h"
#include <vector>
class Product {
public:
    Product(const char* name, int quantity, double price) {
        _name = new char[strlen(name) + 1];
        memcpy(_name, name, strlen(name) + 1);
        _quantity = quantity, _price = price;
    }

    Product() : Product("Default Name", 0, 0.0){}

    ~Product() {
        delete[] _name;
    }

    Product(const Product& other): Product(other._name, other._quantity, other._price){}

    Product& operator=(const Product& other) {
        Product temp(other);
        swap(*this, temp);
        return *this;
    }

    void swap(Product& first, Product& second) {
        std::swap(first._name, second._name);
        std::swap(first._price, second._price);
        std::swap(first._quantity, second._quantity);
    }

    bool operator==(const Product& other) {
        return (abs(other._price - _price) < 1e-8) && (_quantity == other._quantity) && (strcmp(other._name, _name) == 0);
    }

    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        char* ptr = product._name;
        while(*ptr != '\0')  {
            os << *ptr;
            ptr++;
        }
        os << ' ' << product._quantity << ' ' << product._price;
        return os;
    }

private:
    char *_name;
    int _quantity;
    double _price;
};

void print(const my_vector<Product>& v) {
    std::cout << v << std::endl;
}
template <typename T>
void check(my_vector<T>& vector, T* array, int size) {
    assert(size == vector.size());
    for (int i = 0; i < vector.size(); ++i) {
        assert(vector[i] == array[i]);
    }
}


template<typename T>
void test_my_vector(T x, T y, T z) {
    my_vector<T> vector;
    assert(vector.empty());
    vector.push_back(x);
    vector.push_back(y);
    vector.push_back(z);
    assert(!vector.empty());
    assert(vector[0] == x && vector[1] == y && vector[2] == z);
    T test;
    assert((test = vector[0]) == vector[0]);
    assert(vector.size() == 3 && vector.capacity() == 4);
    vector.pop_back();
    assert(vector.size() == 2 && vector.capacity() == 4);
    vector.clear();
    assert(vector.size() == 0 && vector.capacity() == 4);
    vector.push_back(x);
    assert(vector[0] == x);
    vector.resize(2);
    assert(vector.size() == 2 && vector[0] == x && vector[1] == T());
    vector[1] = y;
    vector.push_back(z);
    vector.resize(2);
    assert(vector.size() == 2 && vector[1] == y);
    vector.reserve(5);
    assert(vector.size() == 2 && vector.capacity() == 5);
    my_vector<T> vector1(5);
    assert(vector1.size() == 5 && vector1[0] == T());
    my_vector<T> copy(vector);
    assert(copy.size() == 2 && copy[1] == y && copy[0] == x);
    vector1[0] = x, vector1[1] = y, vector1[2] = z;
    copy = vector1;
    vector1[2] = y;
    assert(copy.size() == vector1.size() && vector1.capacity() == copy.capacity());
    assert(copy[0] == x && copy[1] == y && copy[2] == z);
}

int main() {
    test_my_vector<int>(1, 2, 3);
    Product x("Name1", 1238123, 3.14);
    Product y("Name2", 200, 1.59);
    Product z("Name3", 300, 2.65);
    test_my_vector<Product>(x,y,z);

    return 0;
}


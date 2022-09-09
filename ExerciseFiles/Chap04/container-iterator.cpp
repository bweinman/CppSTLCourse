//  container-iterator.cpp by Bill Weinman [bw.org]
//  as of 2022-09-08
#include <format>
#include <string>
#include <initializer_list>
#include <memory>
#include <iterator>
#include <stdexcept>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

using std::string;
using std::initializer_list;

template<typename T>
class container {
    std::unique_ptr<T[]> c_data{};
    size_t n_elements{};

public:
    class iterator;

    container(initializer_list<T> l) : n_elements(l.size()) {
        c_data = std::make_unique<T[]>(n_elements);
        size_t index{0};
        for(T e : l) {
            c_data[index++] = e;
        }
    }
    
    container(const size_t sz) : n_elements{sz} {
        c_data = std::make_unique<T[]>(n_elements);
    }
    
    size_t size() const {
        return n_elements;
    }

    T& operator[](const size_t index) const {
        return c_data[index];
    }

    T& at(const size_t index) const {
        if(index >= n_elements) {
            throw std::out_of_range("Container::at(): index out of range");
        }
        return c_data[index];
    }

    bool empty() const {
        return (n_elements == 0);
    }

    // begin/end call iterator contsructor
    iterator begin() const { return iterator(c_data.get()); }
    iterator end() const { return iterator(c_data.get() + n_elements); }
};

template<typename T>
class container<T>::iterator {
    T* ptr;

public:
    // iterator constructor with default
    iterator(T* p = nullptr) : ptr(p) {}

    // iterator operators
    iterator& operator++() {
        ++ptr;
        return *this;
    }

    iterator operator++(int) {
        auto ret = *this;
        ++ptr;
        return ret;
    }

    iterator& operator--() {
        --ptr;
        return *this;
    }

    iterator operator--(int) {
        auto ret = *this;
        --ptr;
        return ret;
    }

    T& operator[](const size_t index) const {
        return *(ptr + index);
    }

    // default comparison operator (C++20)
    const auto operator<=>(const iterator& o) const {
        return ptr <=> o.ptr;
    }

    const bool operator==(const iterator& o) const {
        return ptr == o.ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    iterator operator+(const size_t n) const {
        return iterator(ptr + n);
    }

    // non-member + operator (n + it)
    friend const iterator operator+(const size_t n, const iterator& o) {
        return iterator(o.ptr + n);
    }

    const iterator operator-(const size_t n) {
        return iterator(ptr - n);
    }

    const size_t operator-(const iterator& o) {
        if(ptr > o.ptr) return ptr - o.ptr;
        else return 0;
    }

    iterator& operator+=(const size_t n) {
        ptr += n;
        return *this;
    }

    iterator& operator-=(const size_t n) {
        ptr -= n;
        return *this;
    }

};

// standard-required behavior for a contiguous iterator
void unit_tests(const container<string>& x) {
    print("\nunit tests\n{:=>70}\n", ' ');

    auto a = x.begin();
    auto b = x.begin() + 5;
    auto n = b - a;     // n is size_t
    bool r {};

    print("*a: {}\n", *a);
    print("*b: {}\n", *b);
    print("n: {}\n", n);
    
    r = (a += n) == b;
    print("{}: (a += n) == b\n", r);

    a = x.begin();
    r = std::addressof(a += n) == std::addressof(a);
    print("{}: std::addressof(a += n) == std::addressof(a)\n", r);

    a = x.begin();
    auto it1 = (a + n);
    auto it2 = (a += n);
    r = it1 == it2;
    print("{}: (a + n) == (a += n)\n", r);

    a = x.begin();
    r = (a + n) == (n + a);
    print("{}: (a + n) == (n + a)\n", r);
    
    int i{1};
    int j{2};
    r = a + (i + j) == (a + i) + j;
    print("{}: a + (i + j) == (a + i) + j\n", r);

    r = a + 0 == a;
    print("{}: a + 0 == a\n", r);

    b = x.begin() + n;
    r = --b == (a + (n - 1));
    print("{}: --b == (a + (n - 1))\n", r);

    b = x.begin() + n;
    it1 = b += - (long) n;
    b = x.begin() + n;
    it2 = b -= n;
    r = it1 == a && it2 == a;
    print("{}: (b += -n) == a && (b -= n) == a\n", r);

    b = x.begin() + n;
    r = std::addressof(b -= n) == std::addressof(b);
    print("{}: std::addressof(b -= n) == std::addressof(b)\n", r);

    b = x.begin() + n;
    it1 = b - n;
    b = x.begin() + n;
    it2 = b -= n;
    r = it1 == a && it2 == a;
    print("{}: (b - n) == (b -= n)\n", r);

    b = x.begin() + n;
    r = a[n] == *b;
    print("{}: a[n] == *b\n", r);

    r = (a <= b);
    print("{}: (a <= b)\n", r);
}

int main() {
    const container<string> x{"one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine", "ten" };
    print("Container x size: {}\n", x.size());

    print("\nContainer x:\n");
    for (const auto& e : x) print("[{}] ", e);
    print("\n");

    print("\ndirect access elements:\n");
    print("element at(5): {}\n", x.at(5));
    print("element [5]: {}\n", x[5]);
    print("element begin + 5: {}\n", *(x.begin() + 5));
    print("element 5 + begin: {}\n", *(5 + x.begin()));
    print("element begin += 5: {}\n", *(x.begin() += 5));

    // container of int
    print("\ncontainer of int:\n");
    container<int> y(x.size());
    print("Container y size: {}\n", y.size());
    for (const auto& e: y) print("[{}] ", e);
    print("\n");

    print("populate and print:\n");
    for(auto i = 0; i < y.size(); ++i) y[i] = i;
    for (const auto& e: y) print("[{}] ", e);
    print("\n");

    unit_tests(x);
}

//  seq.cpp by Bill Weinman [bw.org]
//  as of 2022-09-08
#include <format>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

template<typename T>
class seq {
    T first_v {};
    T last_v {};

public:
    class iterator;
    seq() = delete;
    seq(T first, T last) : first_v(first), last_v(last) {}
    
    iterator begin() const { return iterator(first_v); }
    iterator end() const { return iterator(last_v + 1); }
};

// iterator for seq<T>
template<typename T>
class seq<T>::iterator {
    T seq_v {};
public:
    explicit iterator(T position = 0) : seq_v(position) {}

    T operator* () const { return seq_v; }

    iterator& operator++ () {
        ++seq_v;
        return *this;
    }

    bool operator!= (const iterator& other) const {
        return seq_v != other.seq_v;
    }
    
    // C++20 default comparison (spaceship) operator
    auto operator<=> (const iterator& other) const {
        return seq_v <=> other.seq_v;
    }
};

int main() {
    seq<int> r(100, 110);

    print("range-for loop:\n");
    for (auto v : r) {
        print("{} ", v);
    }
    print("\n");

    print("C-style for loop:\n");
    for (auto it = r.begin(); it < r.end(); ++it) {
        print("{} ", *it);
    }
    print("\n");
}

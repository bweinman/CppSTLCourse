//  fib-generator.cpp
//  as of 2021-12-03 bw [bw.org]
#include <format>
#include <string_view>
#include <algorithm>
#include <ranges>

using std::string_view;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

class fib_generator {
    using fib_t = unsigned long;

    fib_t stop_{};
    fib_t count_ { 0 };
    fib_t a_ { 0 };
    fib_t b_ { 1 };

    constexpr void do_fib() {
        const fib_t old_b = b_;
        b_ += a_;
        a_  = old_b;
    }

public:
    explicit fib_generator(fib_t stop = 0) : stop_{ stop } {}

    const fib_t& operator*() const { return b_; }

    constexpr fib_generator& operator++() {
        do_fib();
        ++count_;
        return *this;
    }

    fib_generator operator++(int) {
        auto temp{ *this };
        ++*this;
        return temp; 
    }

    bool operator!=(const fib_generator &o) const {
        return count_ != o.count_; 
    }

    bool operator==(const fib_generator&o) const { 
        return count_ == o.count_; 
    }

    const fib_generator& begin() const { return *this; }

    const fib_generator end() const { 
        auto sentinel = fib_generator();
        sentinel.count_ = stop_;
        return sentinel;
    }

    fib_t size() { return stop_; }

};

int main() {
    fib_generator fib(10);
    for (const auto& n : fib) print("{} ", n);
    print("\n");
}

// conditional.cpp by Bill Weinman [bw.org]
// as of 2022-09-08
#include <format>
#include <algorithm>
#include <vector>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

// lambda predicate
auto is_prime = [](const auto& num) {
    if(num <= 1) return false;
    bool primeflag = true;
    for (auto l = 2; l < num; ++l) {
        if (num % l == 0) {
            primeflag = false;
            break;
        }
    }
    return primeflag;
};

void disp_v(auto& v) {
    if(!v.size()) return;
    for(auto e :  v) print("{} ", e);
    print("\n");
}

int main() {
    const std::vector v1 {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    disp_v(v1);

    const std::vector v2 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    disp_v(v2);

    if (std::any_of(v1.begin(), v1.end(), is_prime)) {
        print("true\n");
    } else {
        print("false\n");
    }
}

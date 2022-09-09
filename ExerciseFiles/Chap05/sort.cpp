// sort.cpp by Bill Weinman [bw.org]
// as of 2022-09-08
#include <format>
#include <algorithm>
#include <vector>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

void disp_v(const auto& v) {
    if(!v.size()) return;
    for(auto e :  v) print("{} ", e);
    print("\n");
}

int main() {
    // prime numbers < 100 randomized
    std::vector v1 { 83, 53, 47, 23, 13, 59, 29, 41, 19, 71, 31, 67, 11, 2, 97, 7, 61, 73, 3, 79, 37, 43, 17, 5, 89 };
    disp_v(v1);

    // auto mycomp = [](auto lh, auto rh) { return lh < rh; };
    std::sort(v1.begin(), v1.end());
    disp_v(v1);
}

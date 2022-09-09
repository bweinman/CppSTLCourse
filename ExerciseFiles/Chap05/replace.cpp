// replace.cpp by Bill Weinman [bw.org]
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
    // first 20 fibonacci numbers
    std::vector v1 { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765 };
    disp_v(v1);

    std::replace(v1.begin(), v1.end(), 13, 99999);
    disp_v(v1);
}

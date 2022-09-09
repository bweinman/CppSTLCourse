// algorithm.cpp by Bill Weinman [bw.org]
// as of 2022-08-25
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
    // prime numbers < 100, out of order
    std::vector<int> v1 { 71, 13, 59, 7, 53, 29, 3, 97, 5, 11, 17, 19, 23, 2, 31, 83, 37, 41, 89, 43, 47, 61, 67, 73, 79 };
    disp_v(v1);

    std::sort(v1.begin(), v1.end());
    disp_v(v1);

    int n {42};
    if(std::binary_search(v1.begin(), v1.end(), n)) {
        print("found {}\n", n);
    } else {
        print("{} not found\n", n);
    }
}

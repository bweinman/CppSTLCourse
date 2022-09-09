// span.cpp by Bill Weinman [bw.org]
// as of 2022-09-07
#include <format>
#include <span>

using std::span;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
    print("span over an array\n");
    int ca1[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    span sp1 {ca1};
    print("number of elements: {}\n", sp1.size());
    for(const auto& e : sp1) print("{} ", e);
    print("\n");

    print("\nfront and back\n");
    print("front: {}\n", sp1.front());
    print("back: {}\n", sp1.back());

    print("\noperator []\n");
    print("span[5]: {}\n", sp1[5]);
}

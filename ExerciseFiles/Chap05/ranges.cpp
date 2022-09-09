// ranges.cpp by Bill Weinman [bw.org]
// as of 2022-09-08
#include <format>
#include <vector>
#include <ranges>

namespace ranges = std::ranges;
namespace views = std::ranges::views;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

void disp_v(auto v) {
    if (v.empty()) print("[empty]\n");
    else for (auto e : v) print("{} ", e);
    print("\n");
}

auto even = [](auto i) { return 0 == i % 2; };
auto times2 = [](auto i) { return i * 2; };

int main() {
    std::vector v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    print("v1: ");
    disp_v(v1);

    print("take(5): ");
    disp_v(v1 | views::take(5));
    print("reverse: ");
    disp_v(v1 | views::reverse);
    print("filter(even): ");
    disp_v(v1 | views::filter(even));
    print("iota | take(12) | reverse: ");
    disp_v(views::iota(100) | views::take(12) | views::reverse);
    print("\n");

    std::vector<int> v2{ 6, 1, 2, 10, 9, 5, 8, 3, 4, 7 };
    print("v2: ");
    disp_v(v2);

    std::vector<int> v3(v2.size());
    print("v3: ");
    disp_v(v3);

    ranges::copy(v2, v3.begin());
    print("v3 after copy: ");
    disp_v(v3);

    ranges::sort(v3);
    print("v3 sorted: ");
    disp_v(v3);

    print("v3 transform: even & double: ");
    disp_v(v3 | views::filter(even) | views::transform(times2));
}

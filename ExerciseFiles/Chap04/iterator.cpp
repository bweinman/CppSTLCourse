// iterator.cpp by Bill Weinman [bw.org]
// as of 2022-08-22
#include <format>
#include <vector>

using std::vector;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
    vector<int> vi1 { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vector<int>::iterator it1;   // iterator object
    
    auto ibegin = vi1.begin();
    auto iend = vi1.end();
    
    for (it1 = ibegin; it1 < iend; ++it1) {
        print("{} ", *it1);
    }
    print("\n");
}

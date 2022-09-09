// sv.cpp by Bill Weinman [bw.org]
// as of 2022-09-07
#include <format>
#include <string_view>

using std::string_view;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
    string_view s1 {"This is a string_view"};
    print("s1 is: {}\n", s1);
    
    // size & length
    print("size is same as length: {}\n", s1.size());
    print("size is same as length: {}\n", s1.length());
    
    // compare
    string_view s2 {"this is also a string_view"};
    print("\ncomparison with s2\n");
    print("is s1 == s2? {}\n", s1 == s2 ? "yes" : "no");
    print("copy-assign s2 = s1\n");
    s2 = s1;
    print("is s1 == s2? {}\n", s1 == s2 ? "yes" : "no");
    print("other = \"other string\"\n");
    string_view other {"other string"};
    print("is s1 > other {}\n", s1 > other ? "yes" : "no");
    print("is s1 < other? {}\n", s1 < other ? "yes" : "no");
    print("is other > s1? {}\n", other > s1 ? "yes" : "no");
    print("is other < s1? {}\n", other < s1 ? "yes" : "no");
    
    // iteration
    print("\niteration\n");
    print("each character: ");
    for (const auto& c : s1) {
        print("{} ", c);
    }
    print("\n");

    // substr
    print("\nsubstr: {}\n", s1.substr(5, 5));

    // find
    print("\nfind\n");
    auto pos = s1.find("s");
    print("find first \"s\" in s1 (pos): {}\n", pos);

    // rfind
    print("\nrfind\n");
    pos = s1.rfind("s");
    print("find last \"s\" in s1 (pos): {}\n", pos);
}

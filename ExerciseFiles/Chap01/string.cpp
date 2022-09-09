// string.cpp by Bill Weinman [bw.org]
// as of 2022-09-06
#include <format>
#include <string>

using std::string;

// format-style print() function
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
    string s1 {"This is a string"};
    print("s1 is: {}\n", s1);
    
    // size & length
    print("size is same as length: {}\n", s1.size());
    print("size is same as length: {}\n", s1.length());
    
    // + for concatenation
    print("\nconcatenation\n");
    string s2 {"this is also a string"};
    print("concatenated strings: {}\n", s1 + ":" + s2);

    // compare
    print("\ncomparison\n");
    print("is s1 == s2? {}\n", s1 == s2 ? "yes" : "no");
    print("copy-assign s2 = s1\n");
    s2 = s1;
    print("is s1 == s2? {}\n", s1 == s2 ? "yes" : "no");
    print("other = \"other string\"\n");
    string other {"other string"};
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

    // insert & erase with an iterator
    print("\ninsert\n");
    s1.insert(s1.begin() + 5, 'X');
    print("after insert: {}\n", s1);

    print("\nerase\n");
    s1.erase(s1.begin() + 5);
    print("after erase: {}\n", s1);

    // replace
    print("\nreplace\n");
    s1.replace(5, 2, "ain't");
    print("after replace: {}\n", s1);

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

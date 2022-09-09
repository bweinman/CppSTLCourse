// set.cpp by Bill Weinman [bw.org]
// as of 2022-09-07
#include <format>
#include <string>
#include <set>
#include <unordered_set>

using std::set;
using std::multiset;
using std::unordered_set;

// format-style print() function
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

// print the elements of the set
void print_set(const auto& s) {
    if (s.empty()) return;
    for (const auto& x : s) print("{} ", x);
    print("\n");
}

int main() {
    print("construct set set1\n");
    set<std::string> set1 { "one", "two", "three", "four", "five" };
    print("size of set: {}\n", set1.size());
    print("ordered set is alphabetical\n");
    print_set(set1);
    
    auto sixstr = "six";
    print("\ninsert element {}\n", sixstr);
    set1.insert(sixstr);
    print_set(set1);

    print("\nfind and erase element {}\n", sixstr);
    auto it = set1.find(sixstr);
    if(it != set1.end()) {
        print("{} found\n", *it);
        set1.erase(it);
        print("{} erased\n", sixstr);
    } else {
        print("{} not found\n", sixstr);
    }
    print_set(set1);

    auto fivestr = "five";
    print("\ninserting duplicate element {}\n", fivestr);
    auto rp = set1.insert(fivestr);
    if (rp.second) print("insert succeded\n");
    else print("insert failed\n");
    print_set(set1);

    print("\nconstruct multiset set2\n");
    multiset<std::string> set2 { "one", "two", "three", "four", "five" };
    print_set(set2);

    print("\ninserting duplicate element {} (multiset)\n", fivestr);
    set2.insert(fivestr);
    print_set(set2);

    print("\nconstruct unordered set set3\n");
    unordered_set<std::string> set3 { "one", "two", "three", "four", "five" };
    print("unordered set has no defined order:\n");
    print_set(set3);
}

// list.cpp by Bill Weinman [bw.org]
// as of 2022-09-06
#include <format>
#include <list>
#include <algorithm>

using std::list;

// format-style print() function
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

// print the elements of the list
constexpr void printl(const auto& l) {
    if (l.empty()) {
        print("[empty]\n");
    } else {
        for (const auto& v : l) print("{} ", v);
        print("\n");
    }
}

// lfind() -- simple std::find() wrapper for a list
template<typename T>
auto lfind(const list<T>& l, const T& value) {
    return std::find(l.begin(), l.end(), value);
}

int main() {
    list<int> l1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print("size {}\n", l1.size());
    print("front {}\n", l1.front());
    print("back {}\n", l1.back());
    printl(l1);

    print("\npush back 47\n");
    l1.push_back(47);
    printl(l1);
    
    // insert and erase with iterator
    print("\ninsert 112 before 5\n");
    auto it = lfind(l1, 5);
    if (it != l1.end()) {
        l1.insert(it, 112);
    }
    printl(l1);

    // erase element value 7
    print("\nerase 7\n");
    it = lfind(l1, 7);
    if (it != l1.end()) {
        l1.erase(it);
    }
    printl(l1);

    // remove element value 8
    print("\nremove 8\n");
    l1.remove(8);
    printl(l1);

    // erase a range of elements
    print("\nerase 112 to 9\n");
    auto it1 = lfind(l1, 112);
    auto it2 = lfind(l1, 9);
    if (it1 != l1.end() && it2 != l1.end()) {
        l1.erase(it1, it2);
        printl(l1);
    }
}

// deque.cpp by Bill Weinman <http://bw.org/>
// as of 2022-09-06
#include <format>
#include <deque>
#include <string>

using std::deque;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

// print deque
void printdq(const auto& d) {
    if (d.empty()) return;
    for (const auto& v : d) print("{} ", v);
    print("\n");
}

int main() {
    print("deque of string\n");
    deque<std::string> d1 {"one", "two", "three"};
    print("size: {}, front: {}, back: {}\n", d1.size(), d1.front(), d1.back());
    printdq(d1);

    print("\npush back values\n");
    d1.push_back("four");
    d1.push_back("five");
    printdq(d1);

    print("\nrandom access\n");
    print("element d1[2]: {}\n", d1[2]);
    print("element d1.at(2): {}\n", d1.at(2));

    print("\npop from front\n");
    d1.pop_front();
    printdq(d1);

    print("\npop from back\n");
    d1.pop_back();
    printdq(d1);

    print("\npush front\n");
    d1.push_front("newfront");
    printdq(d1);

    print("\npush back\n");
    d1.push_back("newback");
    printdq(d1);
}

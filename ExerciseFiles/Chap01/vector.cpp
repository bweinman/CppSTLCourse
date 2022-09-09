// vector.cpp by Bill Weinman [bw.org]
// as of 2022-08-20
#include <format>
#include <vector>
#include <string>

// format-style print() function
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

// print the elements of the vector
constexpr void printv(const auto& v) {
    if (v.empty()) {
        print("[empty]\n");
    } else {
        for (const auto& i : v) print("{} ", i);
        print("\n");
    }
}

int main() {
    print("vector from initializer list:\n");
    std::vector<int> v1 { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    printv(v1);

    // info
    print("size: {}\n", v1.size());
    print("front: {}\n", v1.front());
    print("back: {}\n", v1.back());

    // index
    print("element at 5: {}\n", v1[5]);
    print("element at 5: {}\n", v1.at(5));

    // insert
    print("\ninsert 42 at begin + 5:\n");
    v1.insert(v1.begin() + 5, 42);
    printv(v1);

    // erase
    print("\nerase at begin + 5:\n");
    v1.erase(v1.begin() + 5);
    printv(v1);

    // push_back
    print("\npush back 47:\n");
    v1.push_back(47);
    printv(v1);

    // pop_back
    print("\npop_back:\n");
    v1.pop_back();
    printv(v1);

    if(v1.empty()) print("\nv1 is empty.\n");
    else print("\nv1 is not empty.\n");

    // clear
    print("\ninitialize vx:\n");
    std::vector<int> vx { 1, 2, 3, 4, 5 };
    printv(vx);
    print("clear vx:\n");
    vx.clear();
    printv(vx);

    // constructors

    // from C-array
    print("\nvector from C-array:\n");
    constexpr auto size = 10;
    int ia[size] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2(ia, ia + size);
    printv(v2);

    // filled with strings
    print("\nvector filled with string:\n");
    std::vector<std::string> v3(5, "string");
    printv(v3);

    // copy constructor
    print("\nvector (v4) copied from (v3):\n");
    std::vector<std::string> v4(v3);
    printv(v4);

    // move constructor
    print("\nvector (v5) moved from (v4):\n");
    std::vector<std::string> v5(std::move(v4));
    print("v5: "); printv(v5);
    print("v4: "); printv(v4);
}

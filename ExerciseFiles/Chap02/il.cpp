// il.cpp by Bill Weinman [bw.org]
// as of 2022-09-07
#include <format>
#include <initializer_list>

using std::initializer_list;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

template<typename T>
void print_il(const initializer_list<T>& il) {
    if (std::empty(il)) return;
    for (const auto& v : il) print("{} ", v);
    print("\n");
}

template<typename T>
class ilclass {
public:
    ilclass(const std::initializer_list<T>& il) {
        print_il(il);
    }
};

int main() {
    // queue from initializer_list
    print("print_il from initializer list\n");
    print_il({"un", "duex", "trois", "quatre", "cinq"});
    
    // object from initializer_list
    print("\nobject from initializer list\n");
    ilclass<int> o {1, 2, 3, 4, 5};
    
    // for loop
    print("\nfor loop from initializer list\n");
    for (const auto& v : {5, 4, 3, 2, 1}) {
        print("{} ", v);
    }
    print("\n");

    // variable from initializer_list
    print("\nvariable from initializer list\n");
    const auto il = {1, 2, 3, 4, 5};
    ilclass<int> o2 {il};
}

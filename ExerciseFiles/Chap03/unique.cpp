// unique.cpp by Bill Weinman <http://bw.org/>
// as of 2022-09-07
#include <format>
#include <memory>
#include "strc.h"

using bw::strc;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

void message(const char * s) {
    print("\n{}\n", s);
}

// display object value from unique_ptr
void disp(std::unique_ptr<strc>& o) {
    if(o) {
        print("{}\n", o->c_str());
    } else print("null pointer\n");
}

// display array from unique_ptr
void disp_array(std::unique_ptr<int[]>& o, size_t sz) {
    if(o) {
        for (size_t i{}; i < sz; ++i) print("{} ", o[i]);;
    } else print("null pointer\n");
}

int main() {
    message("create unique pointer one");
    std::unique_ptr<strc> a(new strc("one"));
    disp(a);

    message("make_unique two");
    auto b = std::make_unique<strc>("two");
    disp(a);
    disp(b);

    message("reset a to three");
    a.reset(new strc("three"));
    disp(a);
    disp(b);

    message("move b to c");
    auto c = std::move(b);
    disp(a);
    disp(b);
    disp(c);

    message("reset a");
    a.reset();
    disp(a);
    disp(b);
    disp(c);

    message("release c");
    c.release();
    disp(a);
    disp(b);
    disp(c);

    constexpr size_t sz {15};
    message("make_unique array of 15 int");
    auto x = std::make_unique<int[]>(sz);
    disp_array(x, sz);
    print("\n");
    
    message("memcpy to x.get()");
    const int ai[] {1, 2, 3, 4, 5};
    memcpy(x.get(), ai, sizeof(ai));
    disp_array(x, sz);
    print("\n");

    message("end of scope");
}

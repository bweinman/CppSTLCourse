// shared.cpp by Bill Weinman <http://bw.org/>
// as of 2022-08-22

#include <format>
#include <memory>
#include "strc.h"

using bw::strc;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

void message(const char* s) {
    print("\n{}\n", s);
}

// display object value from shared_ptr (with reference count)
void disp(const std::shared_ptr<strc>& o) {
    if(o) print("{} ({})\n", o->c_str(), o.use_count());
    else print("[null]\n");
}

int main() {
    message("create pointer with make_shared one");
    auto a = std::make_shared<strc>("one");
    disp(a);
    
    message("create pointer with new two");
    std::shared_ptr<strc> b(new strc("two"));
    disp(b);

    message("reset a to three");
    a.reset(new strc("three"));
    disp(a);

    message("b = a");
    auto c = a;
    disp(a);
    disp(b);
    disp(c);
    
    message("end of scope");
}

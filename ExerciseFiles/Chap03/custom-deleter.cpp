// custom-deleter.cpp by Bill Weinman <http://bw.org/>
// 2018-10-09

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

// display object value from shared_ptr (with reference count)
void disp(const std::shared_ptr<strc> & o) {
    if(o) print("{} ({})\n", o->c_str(), o.use_count());
    else print("[null]\n");
}

// can be function, functor, or lambda
void deleter(const strc* o) {
    print("deleter: ");
    if(o) {
        print("deleting ({})\n", o->c_str());
        delete o;
    } else print("[null]\n");
}

int main() {
    message("create shared_ptr with deleter");
    std::shared_ptr<strc> a(new strc("thing"), deleter);

    message("disp a");
    disp(a);
    
    message("reset a");
    a.reset();

    message("disp a");
    disp(a);
    
    message("end of scope");
}

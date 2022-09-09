// weak.cpp by Bill Weinman [bw.org]
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

// display object value from shared_ptr (with reference count)
void disp(const std::shared_ptr<strc> & o) {
    if(o) print("{} ({})\n", o->c_str(), o.use_count());
    else print("[null]\n");
}

// display object value from weak_ptr (with reference count before and after lock)
void disp(const std::weak_ptr<strc> & o) {
    // must get a lock to use a weak_ptr
    size_t count = o.use_count(); // weak pointer count
    if(auto sp = o.lock()) {
        print("{} (w:{} s:{})\n", sp->c_str(), count, sp.use_count());
    }
    else print("[null]\n");
}

int main() {
    message("create shared_ptr");
    auto a = std::make_shared<strc>("thing");
    
    message("make several copies");
    auto c1 = a;
    auto c2 = a;
    auto c3 = a;
    auto c4 = a;
    auto c5 = a;
    
    message("reference count should be 6");
    disp(a);
    
    message("create weak_ptr");
    auto w1 = std::weak_ptr<strc>(a);
    disp(w1);
    
    message("destroy copies");
    c1.reset();
    c2.reset();
    c3.reset();
    c4.reset();
    c5.reset();
    
    message("reference count should be 1");
    disp(a);
    
    message("check weak pointer");
    disp(w1);
    
    message("destroy a");
    a.reset();
    
    message("check weak pointer");
    disp(w1);
    
    message("end of scope");
}

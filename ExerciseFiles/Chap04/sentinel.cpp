//  sentinel.cpp by Bill Weinman [bw.org]
//  as of 2022-09-08
#include <format>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

class cstr_it {
    using it_t = const char;
    static it_t sentinel {'\0'};

    it_t* s {};

public:
    cstr_it() = delete;
    cstr_it(const char* str) : s(str) {}

    it_t* c_str() const { return s; }
    
    it_t& operator*() const { return *s; }

    cstr_it& operator++() {
        ++s;
        return *this;
    }

    bool operator!=(it_t) const {
        return s != nullptr && *s != sentinel;
    }

    cstr_it begin() const { return *this; }
    it_t end() const { return sentinel; }
};

void print_cstr(const cstr_it s) {
    print("{}: ", s.c_str());
    for (const char& c : s) {
        print("{:02x} ", c);
    }
    print("\n");
}

int main() {
    const char carray[] {"this is an array"};
    print_cstr(carray);

    const char* cstr {"char * c-string"};
    print_cstr(cstr);
}

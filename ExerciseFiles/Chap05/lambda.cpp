// lambda.cpp by Bill Weinman [bw.org]
// as of 2022-09-08
#include <format>
#include <cctype>   // toupper/tolower
#include <string>
#include <algorithm>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
    char lastc {};
    auto title_case = [&lastc] (const char& c) -> const char {
        auto r = (lastc == ' ' || lastc == '\0') ? std::toupper(c) : std::tolower(c);
        lastc = c;
        return r;
    };

    std::string s {"big light in sky slated to appear in east"};
    print("{}\n", s);
    std::transform(s.begin(), s.end(), s.begin(), title_case);
    print("{}\n", s);
}

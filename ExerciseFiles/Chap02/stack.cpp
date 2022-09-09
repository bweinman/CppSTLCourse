// stack.cpp by Bill Weinman [bw.org]
// as of 2022-09-07
#include <format>
#include <vector>
#include <stack>
#include <string>

using std::stack;
using std::vector;
using std::string;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

void print_stack(const auto& stk) {
    if (stk.empty()) return;
    print("size: {}, top: {}\n", stk.size(), stk.top());
}

int main() {
    print("stk1 from vector<int>\n");
    vector v1 {1, 2, 3, 4, 5};
    stack<int, vector<int>> stk1 {v1};
    print_stack(stk1);

    print("\nstk1 pop element\n");
    stk1.pop();
    print_stack(stk1);

    print("\nstk1 push 42\n");
    stk1.push(42);
    print_stack(stk1);

    print("\nstk2 default stack (deque)\n");
    stack<string> stk2 {};
    for(const auto& s : {"one", "two", "three", "four", "five"}) {
        stk2.push(s);
    }
    print_stack(stk2);

    print("\nstk2 push forty-two\n");
    stk2.push("forty-two");
    print_stack(stk2);

    print("\nstk2 pop\n");
    stk2.pop();
    print_stack(stk2);
}

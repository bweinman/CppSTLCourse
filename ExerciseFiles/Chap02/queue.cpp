// queue.cpp by Bill Weinman [bw.org]
// as of 2022-09-07
#include <format>
#include <list>
#include <queue>
#include <string>

using std::queue;
using std::list;
using std::string;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

void print_queue(const auto& q) {
    if (q.empty()) print("[empty]\n");
    else print("size: {}, front: {}, back: {}\n", q.size(), q.front(), q.back());
}

int main() {
    // queue from list
    print("initialize queue from list\n");
    list<int> l1 {1, 2, 3, 4, 5};
    queue<int, list<int>> q1 {l1};
    print_queue(q1);

    print("\npop one element from q1\n");
    q1.pop();
    print_queue(q1);
    
    print("\npush one element to q1\n");
    q1.push(42);
    print_queue(q1);

    print("\npop all from q1\n");
    while(!q1.empty()) {
        print("{} ", q1.front());
        q1.pop();
    }
    print("\n");
    print_queue(q1);

    // default queue (deque)
    print("\ndefault queue (deque)\n");
    queue<string> q2 {};
    print("push strings onto q2\n");
    for( string s : {"one", "two", "three", "four", "five"} ) {
        q2.push(s);
    }
    print_queue(q2);

    print("\npop all from q2\n");
    while(!q2.empty()) {
        print("{} ", q2.front());
        q2.pop();
    }
    print("\n");
    print_queue(q2);
}

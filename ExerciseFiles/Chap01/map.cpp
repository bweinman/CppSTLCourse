// map.cpp by Bill Weinman <http://bw.org/>
// as of 2022-09-06
#include <format>
#include <string>
#include <map>
#include <unordered_map>

using std::map;
using std::multimap;
using std::unordered_map;

// format-style print() function
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

// print a pair
template<typename A, typename B>
void print_pair(const std::pair<A,B>& p) {
    print("{}: {}\n", p.first, p.second);
}

// print the elements of the map
void print_map(const auto& m) {
    if(m.empty()) return;
    for(const auto& x : m) print_pair(x);
}

int main() {
    print("map of strings from initializer list\n");
    std::map<std::string, std::string> map1 {
        { "Fred", "Father" }, { "Wilma", "Mother" },
        { "Pebbles", "Daughter" }, { "Bamm-Bamm", "Neighbor's Son" }
    };
    print("size: {}\n", map1.size());
    print_map(map1);

    print("\nget some values\n");
    print("Fred: {}\n", map1["Fred"]);
    print("Wilma: {}\n", map1.at("Wilma"));

    // find values
    print("\nfind values\n");
    for(const auto& key : {"Fred", "Wilma", "Pebbles", "foo"}) {
        const auto& p = map1.find(key);
        if (p != map1.end()) print("{}: {}\n", key, p->second);
    }

    print("\ninsert an element");
    map1.insert( { "Barney", "Neighbor" } );
    print("size: {}\n", map1.size());
    print_map(map1);

    // insert duplicate (insert returns a pair<iterator,bool>
    print("\ninsert a duplicate:\n");
    auto rp1 = map1.insert( { "Barney", "Neighbor" } );
    if (rp1.second) print("insert succeded\n");
    else print("insert failed (dup)\n");
    print_map(map1);

    auto findstr = "Barney";
    print("\nfind and erase {}\n", findstr);
    auto it1 = map1.find(findstr);
    if(it1 != map1.end()) {
        print("{} found\n", it1->first);
        map1.erase(it1);
        print("{} erased\n", findstr);
    } else {
        print("not found\n");
    }
    print_map(map1);

    print("\nmultimap (map2)\n");
    std::multimap<std::string, std::string> map2 {
        { "Fred", "Father" }, { "Wilma", "Mother" },
        { "Pebbles", "Daughter" }, { "Bamm-Bamm", "Neighbor's Son" }
    };
    print_map(map2);

    // multimap insert() returns an iterator
    print("\ninsert a duplicate (map2):\n");
    map2.insert( { "Barney", "Neighbor" } );
    map2.insert( { "Barney", "Neighbor" } );
    print_map(map2);
    
    print("\nunordered_map\n");
    std::unordered_map<std::string, std::string> map3 {
        { "Fred", "Father" }, { "Wilma", "Mother" },
        { "Pebbles", "Daughter" }, { "Bamm-Bamm", "Neighbor's Son" }
    };
    print_map(map3);
}

#include <iostream>
#include <cstdlib>
#include <vector>

#include "Tree.h"

int
main(int argc, char* argv[])
{
    std::srand(std::time(0));

    Tree<int> t;

    for (int i = 0; i < 50; ++i) {
        int value = std::rand() % 100;
        t.add(value);
    }
    std::cout << "size: " << t.size() << std::endl;

    Tree<double> s;
    s.add(5.5);
    s.add(90.0);
    s.add(6.1);
    s.add(-55);
    std::cout << "size: " << s.size() << std::endl;

    Tree<std::string> u;
    u.add("zipper");
    u.add("hello");
    u.add("hi");
    u.add("hello");
    u.add("hell");
    u.add("wither");
    u.add("bumbo");
    std::cout << "size: " << u.size() << std::endl;

    std::vector<std::string> strings;
    strings.reserve(u.size());
    for (const auto& x : u) {
        std::cout << x << std::endl;
        strings.push_back(x);
    }

    for (const auto& x : strings) {
        u.remove(x);
    }
    std::string value("wither");
    std::cout << "contains " << value << "? " << u.contains(value) << std::endl;
    u.clear();
    std::cout << "contains " << value << "? " << u.contains(value) << std::endl;
    std::cout << "empty? " << u.isEmpty() << std::endl;

    return 0;
}

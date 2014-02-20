#include <iostream>
#include <cstdlib>
#include <vector>

#include "Tree.h"

int main(int argc, char* argv[])
{
    std::srand(std::time(0));

    Tree<int> t;

    for (int i = 0; i < 50; ++i) {
        int value = std::rand() % 100;
        t.add(value);
    }
    std::cout << std::endl;
    t.print();
    std::cout << "size: " << t.size() << std::endl;

    Tree<double> s;
    s.add(5.5);
    s.add(90.0);
    s.add(6.1);
    s.add(-55);
    s.print();
    std::cout << "size: " << s.size() << std::endl;

    Tree<std::string> u;
    u.add("hello");
    u.add("hi");
    u.add("hello");
    u.add("hell");
    u.add("wither");
    u.add("bumbo");
    u.print();
    std::cout << "size: " << u.size() << std::endl;

    Tree<std::string>::iterator it = u.begin();
    std::cout << *it << std::endl;
    it++;
    std::cout << *it << std::endl;

    return 0;
}

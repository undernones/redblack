#include <iostream>
#include <cstdlib>
#include <vector>

#include "Tree.h"

int main(int argc, char* argv[])
{
    std::srand(std::time(0));

    Tree<int> t;

    std::vector<int> randomData = { 1, 28, 81, /*51, 53, 6, 51, 42, 87, 34,*/ };
    for (int x : randomData) {
        t.add(x);
    }

    //for (int i = 0; i < 10; ++i) {
    //    int value = std::rand() % 100;
    //    std::cout << value << std::endl;
    //    t.add(value);
    //}
    //std::cout << std::endl;
    t.print();
    std::cout << "size: " << t.size() << std::endl;

    return 0;
}

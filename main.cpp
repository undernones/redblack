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
        std::cout << value << " ";
        t.add(value);
    }
    std::cout << std::endl;
    t.print();
    std::cout << "size: " << t.size() << std::endl;

    return 0;
}

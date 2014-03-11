#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "Tree.h"

int
main(int argc, char* argv[])
{
    std::vector<std::string> values = {
        "zipper",
        "hello",
        "hi",
        "hello",
        "hell",
        "wither",
        "bumbo",
    };

    Tree<std::string> u;
    for (auto& x : values) {
        u.add(x);
    }
    std::cout << "size: " << u.size() << std::endl;
    std::ofstream origFile("/tmp/orig.dot", std::ios::out);
    if (!origFile.is_open()) {
        std::cerr << "Could not open /tmp/orig.dot" << std::endl;
        return 1;
    }
    u.dumpToDot(origFile);
    origFile.close();

    for (size_t i = 0; i < values.size(); ++i) {
        auto& x = values[i];
        u.remove(x);
    }
    std::cout << "size: " << u.size() << std::endl;

    return 0;
}

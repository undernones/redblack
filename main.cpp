#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Tree.h"

int
main(int argc, char* argv[])
{
    std::vector<std::string> values = {
        "zipper",
        "hawked",
        "hi",
        "hawked",
        "hawk",
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
        std::stringstream filename;
        filename << "/tmp/bst." << i << ".dot";
        std::ofstream file(filename.str().c_str());
        if (!file.is_open()) {
            std::cerr << "Could not open " << filename.str() << std::endl;
            return 1;
        }
        u.dumpToDot(file);
        file.flush();
        file.close();
        std::cout << "removed: " << x << std::endl;

        for (auto& v : u) {
            std::cout << "value (" << i << "): " << v << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "size: " << u.size() << std::endl;

    return 0;
}

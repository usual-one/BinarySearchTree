#include "BinaryTree.h"

#include <iostream>

int main() {
    auto a = BinaryTree<int>();
    std::cout << a.size() << std::endl;
    a.add(1);
    std::cout << a.size() << std::endl;
    return 0;
}

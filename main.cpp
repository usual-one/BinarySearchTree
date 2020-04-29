#include "BinarySearchTree.h"

#include <iostream>

int main() {
    auto a = BinarySearchTree<int>();
    std::cout << a.size() << std::endl;
    a.add(1);
    std::cout << a.size() << std::endl;
    return 0;
}

#include "BinarySearchTree.h"

#include <iostream>

int main() {
    auto in_order_tree = BinarySearchTree<int>(POST_ORDER);
    in_order_tree.add(5);
    in_order_tree.add(2);
    in_order_tree.add(8);
    std::cout << in_order_tree << std::endl;

    return 0;
}

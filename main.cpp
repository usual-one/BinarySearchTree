#include "BinarySearchTree.h"

#include <iostream>

int main() {
    auto in_order_tree = BinarySearchTree<int>(IN_ORDER);
    std::cout << in_order_tree << std::endl;
    in_order_tree.add(5);
    std::cout << in_order_tree << std::endl;

//    auto reverse_order_tree = BinarySearchTree<int>(REVERSE_ORDER);
//    auto pre_order_tree = BinarySearchTree<int>(PRE_ORDER);
//    auto post_order_tree = BinarySearchTree<int>(POST_ORDER);
//    int numbers[] = {5, 3, 10, 2, 4, 7, 13};
//    auto a = BinarySearchTree<int>(PRE_ORDER);
//    a.addMany(numbers, 7);
//    std::cout << a.size() << std::endl;
//    std::cout << a << std::endl;

    return 0;
}

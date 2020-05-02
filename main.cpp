#include "BinarySearchTree.h"

#include <iostream>

int custom_comparator(int a, int b) {
    if (a < b) {
        return 1;
    } else if (a > b) {
        return -1;
    }
    return 0;
}

int main() {
    std::cout << "--- TESTING STARTED ---" << std::endl;
    auto first_tree = BinarySearchTree<int>(IN_ORDER); // testing constructor

    std::cout << "first_tree = " << first_tree << std::endl; // testing <<
    std::cout << "must be      {}" << std::endl;

    std::cout << "first_tree size = " << first_tree.size() << std::endl; // testing size()
    std::cout << "must be           0" << std::endl;

    first_tree.add(5); // testing add()
    std::cout << "first_tree = " << first_tree << std::endl;
    std::cout << "must be      {5}" << std::endl;
    std::cout << "first_tree size = " << first_tree.size() << std::endl;
    std::cout << "must be           1" << std::endl;

    int numbers_to_add[] = {8, 2, 6, 4};
    first_tree.addMany(numbers_to_add, 4); // testing addMany()
    std::cout << "first_tree = " << first_tree << std::endl;
    std::cout << "must be      {2, 4, 5, 6, 8}" << std::endl;

    std::cout << "first_tree min = " << first_tree.min() << std::endl; // testing min()
    std::cout << "must be          2" << std::endl;

    std::cout << "first_tree max = " << first_tree.max() << std::endl; // testing max()
    std::cout << "must be          8" << std::endl;

    std::cout << "first_tree contains = " << first_tree.contains(2)
              << std::endl; // testing contains()
    std::cout << "must be               1" << std::endl;

    auto second_tree = BinarySearchTree<int>(IN_ORDER);
    int numbers_to_add2[] = {5, 2, 8};
    second_tree.addMany(numbers_to_add2, 3);
    std::cout << "first_tree contains second = " << first_tree.contains(second_tree)
              << std::endl; // testing contains() for trees
    std::cout << "must be                      1" << std::endl;

    second_tree.add(1);
    first_tree.extend(second_tree); // testing extend()
    std::cout << "first_tree = " << first_tree << std::endl;
    std::cout << "must be      {1, 2, 4, 5, 6, 8}" << std::endl;

    first_tree.remove(6); // testing remove()
    std::cout << "first_tree = " << first_tree << std::endl;
    std::cout << "must be      {1, 2, 4, 5, 8}" << std::endl;

    int numbers_to_remove[] = {2, 5};
    first_tree.removeMany(numbers_to_remove, 2); // testing removeMany()
    std::cout << "first_tree = " << first_tree << std::endl;
    std::cout << "must be      {1, 4, 8}" << std::endl;

    first_tree.clear(); // testing clear()
    std::cout << "first_tree = " << first_tree << std::endl;
    std::cout << "must be      {}" << std::endl;
    std::cout << "first_tree size = " << first_tree.size() << std::endl;
    std::cout << "must be           0" << std::endl;

    auto third_tree = first_tree; // testing operator =
    std::cout << "third_tree = " << third_tree << std::endl;
    std::cout << "must be      {}" << std::endl;

    third_tree += second_tree; // testing operator +=
    std::cout << "third_tree = " << third_tree << std::endl;
    std::cout << "must be      {1, 2, 5, 8}" << std::endl;

    auto fourth_tree = first_tree + second_tree; // testing operator +
    std::cout << "fourth_tree = " << fourth_tree << std::endl;
    std::cout << "must be       {1, 2, 5, 8}" << std::endl;

    std::cout << "operator == " << (first_tree == fourth_tree)
              << std::endl; // testing operator ==
    std::cout << "must be     0" << std::endl;

    std::cout << "operator != " << (first_tree != fourth_tree)
              << std::endl; // testing operator !=
    std::cout << "must be     1" << std::endl;

    int *array_from_tree = second_tree.toArray(); // testing toArray()
    std::cout << "array_from_tree = ";
    for (size_t i = 0; i < 4; i++) {
        std::cout << array_from_tree[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "must be           1 2 5 8" << std::endl;

    second_tree.setComparator(custom_comparator); // testing setComparator
    second_tree.clear();
    second_tree.addMany(array_from_tree, 4);
    std::cout << "second_tree = " << second_tree << std::endl;
    std::cout << "must be       {8, 5, 2, 1}" << std::endl;

    fourth_tree.setOrder(IN_ORDER); // testing setOrder
    std::cout << "fourth_tree = " << fourth_tree << std::endl;
    std::cout << "must be       {1, 2, 5, 8}" << std::endl;
    fourth_tree.setOrder(REVERSE_ORDER);
    std::cout << "fourth_tree = " << fourth_tree << std::endl;
    std::cout << "must be       {8, 5, 2, 1}" << std::endl;
    fourth_tree.setOrder(PRE_ORDER);
    std::cout << "fourth_tree = " << fourth_tree << std::endl;
    std::cout << "must be       {1, 2, 5, 8}" << std::endl;
    fourth_tree.setOrder(POST_ORDER);
    std::cout << "fourth_tree = " << fourth_tree << std::endl;
    std::cout << "must be       {8, 5, 2, 1}" << std::endl;


    auto it = *fourth_tree.iteratorBegin(); // testing constructor & iteratorBegin()

    std::cout << "iterator = " <<  *it << std::endl; // testing operator *
    std::cout << "must be    8" << std::endl;

    std::cout << "iterator = " << it.value() << std::endl; // testing value()
    std::cout << "must be    8" << std::endl;

    std::cout << "it.hasNext() = " << it.hasNext() << std::endl; // testing hasNext()
    std::cout << "must be        1" << std::endl;

    std::cout << "it.hasPrevious() = " << it.hasPrevious() << std::endl; // testing hasPrevious()
    std::cout << "must be            0" << std::endl;

    std::cout << "iterator++ = " << *(it++) << std::endl; // testing operator ++(int)
    std::cout << "must be      8" << std::endl;

    std::cout << "++iterator = " << *(++it) << std::endl; // testing operator ++
    std::cout << "must be      2" << std::endl;

    std::cout << "iterator-- = " << *(it--) << std::endl; // testing operator --(int)
    std::cout << "must be      2" << std::endl;

    std::cout << "--iterator = " << *(--it) << std::endl; // testing operator --
    std::cout << "must be      8" << std::endl;

    auto it_end = *fourth_tree.iteratorEnd(); // testing iteratorEnd()

    std::cout << "it_end.isEnd() = " << it_end.isEnd() << std::endl; // testing isEnd()
    std::cout << "must be          1" << std::endl;

    it_end -= 1; // testing operator -=
    std::cout << "it_end.isEnd() = " << it_end.isEnd() << std::endl;
    std::cout << "must be          0" << std::endl;

    it_end += 1; // testing operator +=
    std::cout << "it_end.isEnd() = " << it_end.isEnd() << std::endl;
    std::cout << "must be          1" << std::endl;

    std::cout << "operator == " << (it_end == it) << std::endl; // testing operator ==
    std::cout << "must be     0" << std::endl;

    std::cout << "operator != " << (it_end != it) << std::endl; // testing operator !=
    std::cout << "must be     1" << std::endl;

    std::cout << "operator <= " << (it_end <= it) << std::endl; // testing operator <=
    std::cout << "must be     0" << std::endl;

    std::cout << "operator >= " << (it_end >= it) << std::endl; // testing operator >=
    std::cout << "must be     1" << std::endl;

    std::cout << "operator < " << (it_end < it) << std::endl; // testing operator <
    std::cout << "must be    0" << std::endl;

    std::cout << "operator > " << (it_end > it) << std::endl; // testing operator >
    std::cout << "must be    1" << std::endl;

    it_end.begin(); // testing begin()
    std::cout << "it_end.isEnd() = " << (it_end.isEnd() && !it_end.hasPrevious()) << std::endl;
    std::cout << "must be          0" << std::endl;

    it_end.end(); // testing end()
    std::cout << "it_end.isEnd() = " << it_end.isEnd() << std::endl;
    std::cout << "must be          1" << std::endl;

    auto it_add = it + 2; // testing operator +
    std::cout << "iterator = " << *it_add << std::endl;
    std::cout << "must be    2" << std::endl;

    auto it_subtract = it_add - 2; // testing operator -
    std::cout << "iterator = " << *it_subtract << std::endl;
    std::cout << "must be    8" << std::endl;

    std::cout << "--- TESTING FINISHED ---" << std::endl;

    delete [] array_from_tree;
    return 0;
}

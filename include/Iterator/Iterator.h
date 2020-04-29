#ifndef CONTAINER_ITERATOR_H
#define CONTAINER_ITERATOR_H

template<typename T>
class BinarySearchTree;

template<typename T>
class Iterator {
public:
    Iterator() = delete;

    Iterator(const BinarySearchTree<T> &tree);

    Iterator<T> begin();

    Iterator<T> end();

    Iterator<T> next();

    Iterator<T> previous();

    bool is_end();

    T value();

    Iterator<T> &operator++();

    Iterator<T> &operator--();

    T &operator*();

    bool operator==(Iterator<T> &it);

    bool operator!=(Iterator<T> &it);

    bool operator<(Iterator<T> &it);

    bool operator>(Iterator<T> &it);

    bool operator<=(Iterator<T> &it);

    bool operator>=(Iterator<T> &it);

private:
    BinarySearchTree<T> *current_;
};

#endif  // CONTAINER_ITERATOR_H

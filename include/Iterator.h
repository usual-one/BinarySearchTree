#ifndef CONTAINER_ITERATOR_H
#define CONTAINER_ITERATOR_H

template<typename T>
class BinaryTree;

template<typename T>
class Iterator{
public:
    Iterator() = delete;

    Iterator(const BinaryTree<T> &tree);

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
    BinaryTree<T> *current_;
};

#endif //CONTAINER_ITERATOR_H

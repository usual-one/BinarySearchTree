#ifndef CONTAINER_ITERATOR_H
#define CONTAINER_ITERATOR_H

#include <cstdlib>

template<typename T>
class BinarySearchTree;

template<typename T>
class Iterator {
public:
    Iterator() = delete;

    explicit Iterator(const BinarySearchTree<T> *tree);

    ~Iterator();

    Iterator<T> begin(const BinarySearchTree<T> *tree);

    Iterator<T> end(const BinarySearchTree<T> *tree);

    bool is_end();

    bool hasNext();

    bool hasPrevious();

    void next();

    void previous();

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

protected:
    T *flattened_tree_;
    size_t size_;
    size_t pos_;
};

template<typename T>
Iterator<T>::Iterator(const BinarySearchTree<T> *tree) {
    flattened_tree_ = tree->toArray();
    size_ = tree->size();
    pos_ = 0;
}

template<typename T>
Iterator<T>::~Iterator() {
    delete [] flattened_tree_;
}

template<typename T>
Iterator<T> Iterator<T>::begin(const BinarySearchTree<T> *tree) {
    return Iterator<T>(tree);
}

template<typename T>
Iterator<T> Iterator<T>::end(const BinarySearchTree<T> *tree) {
    Iterator<T> it(tree);
    it.pos_ = it.size_;
    return it;
}

template<typename T>
bool Iterator<T>::is_end() {
    return pos_ == size_;
}

template<typename T>
bool Iterator<T>::hasNext() {
    return pos_ < size_ - 1;
}

template<typename T>
bool Iterator<T>::hasPrevious() {
    return pos_ > 0;
}

template<typename T>
void Iterator<T>::next() {
    if (hasNext()) {
        pos_++;
    }
}

template<typename T>
void Iterator<T>::previous() {
    if (hasPrevious()) {
        pos_++;
    }
}

template<typename T>
T Iterator<T>::value() {
    return flattened_tree_[pos_];
}

template<typename T>
Iterator<T> &Iterator<T>::operator++() {
    return this->next();
}

template<typename T>
Iterator<T> &Iterator<T>::operator--() {
    return this->previous();
}

template<typename T>
T &Iterator<T>::operator*() {
    return this->value();
}

template<typename T>
bool Iterator<T>::operator!=(Iterator<T> &it) {
    return !(this == it);
}

template<typename T>
bool Iterator<T>::operator<=(Iterator<T> &it) {
    return this < it or this == it;
}

template<typename T>
bool Iterator<T>::operator>=(Iterator<T> &it) {
    return this > it or this == it;
}

template<typename T>
bool Iterator<T>::operator==(Iterator<T> &it) {
    if (size_ != it.size_) {
        return false;
    }
    if (pos_ != it.pos_) {
        return false;
    }
    for (size_t i = 0; i < size_; i++) {
        if (*(flattened_tree_[i]) != *(it.flattened_tree_[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Iterator<T>::operator<(Iterator<T> &it) {
    return pos_ < it.pos_;
}

template<typename T>
bool Iterator<T>::operator>(Iterator<T> &it) {
    return pos_ > it.pos_;
}

#endif  // CONTAINER_ITERATOR_H

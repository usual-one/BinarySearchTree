#ifndef CONTAINER_BINARY_SEARCH_TREE_H
#define CONTAINER_BINARY_SEARCH_TREE_H

#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <memory>
#include <ostream>
#include "BSTException.h"
#include "BSTIteratorException.h"

enum tree_order {
    IN_ORDER,
    REVERSE_ORDER,
    PRE_ORDER,
    POST_ORDER
};

template<typename T>
class Iterator;

template<typename T>
class BinarySearchTree {
public:
    explicit BinarySearchTree(tree_order order = IN_ORDER,
                              std::function<int(T, T)> comparator = defaultCompare);
//    Конструктор по умолчанию

    BinarySearchTree(const BinarySearchTree<T> &obj);
//    Конструктор копирования

    BinarySearchTree(const BinarySearchTree<T> &&obj) noexcept;
//    Конструктор переноса

    BinarySearchTree(std::initializer_list<T> &lst, tree_order order = IN_ORDER,
                     std::function<int(T, T)> comparator = defaultCompare);
//    Конструктор со списком инициализации

    ~BinarySearchTree() noexcept;
//    Деструктор

    void add(const T &elem);
//    Добавить элемент

    void addMany(const T *arr, size_t size);
//    Добавить элементы из указанного массива

    void clear();
//    Очистить дерево (удалить все элементы)

    bool contains(const T &elem);
//    Проверить имеется ли указанный элемент в дереве

    bool contains(const BinarySearchTree<T> &obj) const;
//    Проверить имеется ли указанная ветка в дереве

    void copy(const BinarySearchTree<T> &obj);
//    Делает ветку точной копией указанной ветки

    void extend(const BinarySearchTree<T> &obj);
//    Расширить дерево, путем сложения его с данным

    bool isEmpty() const;
//    Проверить на пустоту

    std::unique_ptr<Iterator<T>> iteratorBegin() const;
//    Получить итератор на начало дерева

    std::unique_ptr<Iterator<T>> iteratorEnd() const;
//    Получить итератор на фиктивный элемент, следующий за последним

    T max();
//    Вернуть максимальный элемент

    T min();
//    Вернуть минимальный элемент

    void remove(const T &elem);
//    Удалить элемент

    void removeMany(const T *arr, size_t size);
//    Удалить элементы из указанного массива

    void setComparator(std::function<int(T, T)> comparator);
//    Смена функции сравнения

    void setOrder(tree_order order);
//    Смена порядка прохода по дереву

    size_t size() const;
//    Количество элементов в дереве

    T *toArray() const;
//    Конвертировать ветку в массив

    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &obj);
//    Перегрузка оператора присваивания

    BinarySearchTree<T> &operator+=(const BinarySearchTree<T> &obj);
//    Сложение с другим деревом (аналогично extend), результат сложения в this

    template<typename _T>
    friend BinarySearchTree<_T>
    operator+(const BinarySearchTree<_T> &obj1, const BinarySearchTree<_T> &obj2);
//    Сложение с другим деревом (аналогично extend)

    template<typename _T>
    friend std::ostream &operator<<(std::ostream &os, const BinarySearchTree<_T> &obj);
//    Перегрузка оператора вывода на поток

    template<typename _T>
    friend bool operator==(const BinarySearchTree<_T> &obj1, const BinarySearchTree<_T> &obj2);
//    Перегрузка оператора равенства

    template<typename _T>
    friend bool operator!=(const BinarySearchTree<_T> &obj1, const BinarySearchTree <_T> &obj2);
//    Перегрузка оператора неравенства

private:
    void addToArray(T *arr, size_t *current_size) const;
//    Добавить ветку в массив

    void dealloc();
//    Освободить память всей текущей ветки

    static int defaultCompare(T a, T b);
//    Функция сравнения элементов по умолчанию

    BinarySearchTree<T> *find(const T &elem);
//    Найти элемент со значением равным указанному

    bool isGreaterChild() const;
//    Является ли текущий элемент большим по отношению к родителю

    bool isSmallerChild() const;
//    Является ли текущий элемент меньшим по отношению к родителю

    bool isRoot() const;
//    Является ли текущая ветка корнем

    BinarySearchTree<T> *maxElement();
//    Найти элемент с максимальным значением

    BinarySearchTree<T> *minElement();
//    Найти элемент с минимальным значением

    BinarySearchTree<T> *parent_; // root.parent_ == nullptr
    BinarySearchTree<T> *smaller_child_;
    BinarySearchTree<T> *greater_child_;
    T value_;

    bool empty_;

    tree_order order_;
    std::function<int(T, T)> comparator_;
};


template<typename T>
BinarySearchTree<T>::BinarySearchTree(tree_order order, std::function<int(T, T)> comparator) {
    parent_ = nullptr;
    smaller_child_ = nullptr;
    greater_child_ = nullptr;
    value_ = 0;
    empty_ = true;
    order_ = order;
    comparator_ = comparator;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &obj) {
    parent_ = nullptr;
    smaller_child_ = nullptr;
    greater_child_ = nullptr;
    copy(obj);
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &&obj) noexcept {
    empty_ = true;
    order_ = obj.order_;
    comparator_ = obj.comparator_;
    addMany(obj.toArray(), obj.size());
    obj.~BinarySearchTree();
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(std::initializer_list<T> &lst, tree_order order,
                                      std::function<int(T, T)> comparator) {
    empty_ = true;
    order_ = order;
    comparator_ = comparator;
    for (auto el : lst) {
        add(el);
    }
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() noexcept {
    dealloc();
}

template<typename T>
void BinarySearchTree<T>::add(const T &elem) {
    if (empty_) {
        empty_ = false;
        value_ = elem;
        return;
    }
    if (!comparator_(elem, value_)) {
        throw BSTDuplicateValueException("duplicate value to add");
    }
    if (comparator_(elem, value_) < 0) {
        if (!smaller_child_) {
            smaller_child_ = new BinarySearchTree(order_, comparator_);
            smaller_child_->parent_ = this;
        }
        smaller_child_->add(elem);
    } else {
        if (!greater_child_) {
            greater_child_ = new BinarySearchTree(order_, comparator_);
            greater_child_->parent_ = this;
        }
        greater_child_->add(elem);
    }
}

template<typename T>
void BinarySearchTree<T>::addMany(const T *arr, size_t size) {
    bool duplicates = false;
    for (size_t i = 0; i < size; i++) {
        try {
            add(arr[i]);
        } catch (BSTDuplicateValueException &err) {
            duplicates = true;
        }
    }
    if (duplicates) {
        throw BSTDuplicateValueException("duplicate values to add");
    }
}

template<typename T>
void BinarySearchTree<T>::clear() {
    dealloc();
    empty_ = true;
}

template<typename T>
bool BinarySearchTree<T>::contains(const T &elem) {
    return (bool) find(elem);
}

template<typename T>
bool BinarySearchTree<T>::contains(const BinarySearchTree<T> &obj) const {
    if (obj.isEmpty()) {
        throw BSTEmptyException("can't check empty tree presence");
    }
    bool existence = (value_ == obj.value_);
    if (smaller_child_) {
        if (existence && obj.smaller_child_) {
            existence = smaller_child_->contains(*obj.smaller_child_);
        } else if (!existence) {
            existence = smaller_child_->contains(obj);
        }
    }
    if (greater_child_) {
        if (existence && obj.greater_child_) {
            existence = greater_child_->contains(*obj.greater_child_);
        } else if (!existence) {
            existence = greater_child_->contains(obj);
        }
    }
    return existence;
}

template<typename T>
void BinarySearchTree<T>::copy(const BinarySearchTree<T> &obj) {
    clear();
    order_ = obj.order_;
    comparator_ = obj.comparator_;

    if (!obj.isEmpty()) {
        value_ = obj.value_;
        if (obj.smaller_child_) {
            add(obj.smaller_child_->value_);
            smaller_child_->copy(*obj.smaller_child_);
        }
        if (obj.greater_child_) {
            add(obj.greater_child_->value_);
            greater_child_->copy(*obj.greater_child_);
        }
    }
}

template<typename T>
void BinarySearchTree<T>::extend(const BinarySearchTree<T> &obj) {
    if (obj.isEmpty()) {
        throw BSTEmptyException("empty tree to extend by");
    }
    for (auto it = *(obj.iteratorBegin()); it < *(obj.iteratorEnd()); it++) {
        try {
            add(*it);
        } catch (BSTDuplicateValueException &err) {}
    }
}

template<typename T>
bool BinarySearchTree<T>::isEmpty() const {
    return empty_;
}

template<typename T>
std::unique_ptr<Iterator<T>> BinarySearchTree<T>::iteratorBegin() const {
    auto it = std::make_unique<Iterator<T>>(*this);
    it->begin();
    return it;
}

template<typename T>
std::unique_ptr<Iterator<T>> BinarySearchTree<T>::iteratorEnd() const {
    auto it = std::make_unique<Iterator<T>>(*this);
    it->end();
    return it;
}

template<typename T>
T BinarySearchTree<T>::max() {
    if (isEmpty()) {
        throw BSTEmptyException("can't find empty tree max value");
    }
    return maxElement()->value_;
}

template<typename T>
T BinarySearchTree<T>::min() {
    if (isEmpty()) {
        throw BSTEmptyException("can't find empty tree min value");
    }
    return minElement()->value_;
}

template<typename T>
void BinarySearchTree<T>::remove(const T &elem) {
    BinarySearchTree<T> *found = find(elem);
    if (!found) {
        throw BSTNonexistentValueException("nonexistent value to remove");
    }

    BinarySearchTree *successor = nullptr;
    if (found->smaller_child_ && found->greater_child_) {
        if (found->smaller_child_->size() > found->greater_child_->size()) {
            successor = found->smaller_child_->maxElement();
            T successor_value = successor->value_;
            remove(successor_value);
            found->value_ = successor_value;
        } else {
            successor = found->greater_child_->minElement();
            T successor_value = successor->value_;
            remove(successor_value);
            found->value_ = successor_value;
        }
        return;
    }

    if (found->smaller_child_ && !found->greater_child_) {
        successor = found->smaller_child_;
        found->smaller_child_ = nullptr;
        successor->parent_ = found->parent_;
    }
    if (found->greater_child_ && !found->smaller_child_) {
        successor = found->greater_child_;
        found->greater_child_ = nullptr;
        successor->parent_ = found->parent_;
    }

    if (!found->isRoot()) {
        if (found->isSmallerChild()) {
            found->parent_->smaller_child_ = successor;
        } else if (found->isGreaterChild()) {
            found->parent_->greater_child_ = successor;
        }
        delete found;
    }
}

template<typename T>
void BinarySearchTree<T>::removeMany(const T *arr, size_t size) {
    bool nonexistent = false;
    for (size_t i = 0; i < size; i++) {
        try {
            remove(arr[i]);
        } catch (BSTNonexistentValueException &err) {
            nonexistent = true;
        }
    }
    if (nonexistent) {
        throw BSTNonexistentValueException("nonexistent values to remove");
    }
}

template<typename T>
void BinarySearchTree<T>::setComparator(std::function<int(T, T)> comparator) {
    comparator_ = comparator;
    if (smaller_child_) {
        smaller_child_->setComparator(comparator);
    }
    if (greater_child_) {
        greater_child_->setComparator(comparator);
    }
}

template<typename T>
void BinarySearchTree<T>::setOrder(tree_order order) {
    order_ = order;
    if (smaller_child_) {
        smaller_child_->setOrder(order);
    }
    if (greater_child_) {
        greater_child_->setOrder(order);
    }
}

template<typename T>
size_t BinarySearchTree<T>::size() const {
    size_t size = 0;
    if (isEmpty()) {
        return size;
    }
    size++;

    if (smaller_child_) {
        size += smaller_child_->size();
    }
    if (greater_child_) {
        size += greater_child_->size();
    }
    return size;
}

template<typename T>
T *BinarySearchTree<T>::toArray() const {
    if (isEmpty()) {
        throw BSTEmptyException("can't convert empty tree");
    }
    T *arr = new T[size()];
    size_t arr_size = 0;
    addToArray(arr, &arr_size);
    return arr;
}

template<typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(const BinarySearchTree<T> &obj) {
    if (this == obj) {
        return *this;
    }
    empty_ = true;
    order_ = obj.order_;
    comparator_ = obj.comparator_;
    addMany(obj.toArray(), obj.size());
    return *this;
}

template<typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator+=(const BinarySearchTree<T> &obj) {
    extend(obj);
    return *this;
}

template<typename _T>
BinarySearchTree<_T> operator+(const BinarySearchTree<_T> &obj1, const BinarySearchTree<_T> &obj2) {
    BinarySearchTree<_T> sum(obj1);
    sum.extend(obj2);
    return sum;
}

template<typename _T>
std::ostream &operator<<(std::ostream &os, const BinarySearchTree<_T> &obj) {
    os << "{";
    if (!obj.isEmpty()) {
        auto it_begin = *obj.iteratorBegin();
        auto it_end = --(*obj.iteratorEnd());
        for (auto it = it_begin; it < it_end; it++) {
            os << *it << ", ";
        }
        os << *it_end;
    }
    os << "}";
    return os;
}

template<typename _T>
bool operator==(const BinarySearchTree<_T> &obj1, const BinarySearchTree<_T> &obj2) {
    if (obj1.order_ != obj2.order_) {
        return false;
    }
    if (obj1.size() != obj2.size()) {
        return false;
    }
    if (!obj1.isEmpty()) {
        for (auto it1 = *obj1.iteratorBegin(), it2 = *obj2.iteratorBegin(); it1 < *obj1.iteratorEnd();
             it1++, it2++) {
            if (*it1 != *it2) {
                return false;
            }
        }
    }
    return true;
}

template<typename _T>
bool operator!=(const BinarySearchTree<_T> &obj1, const BinarySearchTree <_T> &obj2) {
    return !(obj1 == obj2);
}

template<typename T>
void BinarySearchTree<T>::addToArray(T *arr, size_t *current_size) const {
    size_t *size = current_size;
    if (order_ == IN_ORDER) {
        if (smaller_child_) {
            smaller_child_->addToArray(arr, size);
        }
        arr[(*size)++] = value_;
        if (greater_child_) {
            greater_child_->addToArray(arr, size);
        }
    } else if (order_ == REVERSE_ORDER) {
        if (greater_child_) {
            greater_child_->addToArray(arr, size);
        }
        arr[(*size)++] = value_;
        if (smaller_child_) {
            smaller_child_->addToArray(arr, size);
        }
    } else if (order_ == PRE_ORDER) {
        arr[(*size)++] = value_;
        if (smaller_child_) {
            smaller_child_->addToArray(arr, size);
        }
        if (greater_child_) {
            greater_child_->addToArray(arr, size);
        }
    } else if (order_ == POST_ORDER) {
        if (smaller_child_) {
            smaller_child_->addToArray(arr, size);
        }
        if (greater_child_) {
            greater_child_->addToArray(arr, size);
        }
        arr[(*size)++] = value_;
    }
}

template<typename T>
void BinarySearchTree<T>::dealloc() {
    if (smaller_child_) {
        smaller_child_->dealloc();
        delete smaller_child_;
        smaller_child_ = nullptr;
    }
    if (greater_child_) {
        greater_child_->dealloc();
        delete greater_child_;
        greater_child_ = nullptr;
    }
}

template<typename T>
int BinarySearchTree<T>::defaultCompare(T a, T b) {
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}

template<typename T>
BinarySearchTree<T> *BinarySearchTree<T>::find(const T &elem) {
    if (empty_) {
        return nullptr;
    }
    if (elem < value_ && smaller_child_) {
        return smaller_child_->find(elem);
    }
    if (elem > value_ && greater_child_) {
        return greater_child_->find(elem);
    }
    if (elem == value_) {
        return this;
    }
    return nullptr;
}

template<typename T>
bool BinarySearchTree<T>::isGreaterChild() const {
    if (isRoot()) {
        return false;
    }
    return (value_ == parent_->greater_child_->value_);
}

template<typename T>
bool BinarySearchTree<T>::isSmallerChild() const {
    if (isRoot()) {
        return false;
    }
    return (value_ == parent_->smaller_child_->value_);
}

template<typename T>
bool BinarySearchTree<T>::isRoot() const {
    return !((bool) parent_);
}

template<typename T>
BinarySearchTree<T> *BinarySearchTree<T>::maxElement() {
    BinarySearchTree<T> *maximum = this;
    if (greater_child_) {
        maximum = greater_child_->maxElement();
    }
    return maximum;
}

template<typename T>
BinarySearchTree<T> *BinarySearchTree<T>::minElement() {
    BinarySearchTree<T> *minimum = this;
    if (smaller_child_) {
        minimum = smaller_child_->minElement();
    }
    return minimum;
}



template<typename T>
class Iterator {
public:
    Iterator() = delete;
//    Конструктор по умолчанию (удален)

    explicit Iterator(const BinarySearchTree<T> &tree);
//    Перегрузка конструктора

    Iterator(const Iterator<T> &obj);
//    Конструктор копирования

    ~Iterator();
//    Деструктор

    Iterator<T> &begin();
//    Получить итератор на первый элемент

    Iterator<T> &end();
//    Получить итератор на фиктивный элемент, следующий за последним

    bool hasNext();
//    Имеет ли итератор следующий элемент (в т. ч. фиктивный)

    bool hasPrevious();
//    Имеет ли итератор предыдущий элемент

    bool isEnd();
//    Находится ли итератор наа фиктивном элементе, следующем за последним

    void next();
//    Сместиться на следующий элемент

    void previous();
//    Сместиться на предыдущий элемент

    T &value();
//    Получить значение текущего элемента

    Iterator<T> &operator+=(int offset);
//    Сместить текущий итератор на offset позиций вперед

    Iterator<T> &operator-=(int offset);
//    Сместить текущий итератор на offset позиций назад

    Iterator<T> &operator++();
//    Сместить итератор на одну позицию вперед и вернуть новое значение

    Iterator<T> &operator--();
//    Сместить итератор на одну позицию назад и вернуть новое значение

    Iterator<T> operator++(int);
//    Сместить итератор на одну позицию вперед и вернуть прежнее значение

    Iterator<T> operator--(int);
//    Сместить итератор на одну позицию назад и вернуть прежнее значение

    T &operator*();
//    Получить значение текущего элемента

    bool operator==(Iterator<T> &it);
//    Перегрузка оператора равенства

    bool operator!=(Iterator<T> &it);
//    Перегрузка оператора неравенства

    bool operator<(Iterator<T> &it);
//    Перегрузка оператора "меньше" (сравниваются позиции итераторов)

    bool operator>(Iterator<T> &it);
//    Перегрузка оператора "больше" (сравниваются позиции итераторов)

    bool operator<=(Iterator<T> &it);
//    Перегрузка оператора "меньше или равно" (сравниваются позиции итераторов)

    bool operator>=(Iterator<T> &it);
//    Перегрузка оператора "больше или равно" (сравниваются позиции итераторов)

    template<typename _T>
    friend Iterator<_T> operator+(const Iterator<_T> &obj, int offset);
//    Вернуть итератор, смещенный на offset позиций вперед

    template<typename _T>
    friend Iterator<_T> operator-(const Iterator<_T> &obj, int offset);
//    Вернуть итератор, смещенный на offset позиций назад

private:
    T *flattened_tree_;
    size_t size_;
    size_t pos_;
};

template<typename T>
Iterator<T>::Iterator(const BinarySearchTree<T> &tree) {
    try {
        flattened_tree_ = tree.toArray();
    } catch (BSTEmptyException &err) {
        flattened_tree_ = nullptr;
    }
    size_ = tree.size();
    pos_ = 0;
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T> &obj) {
    size_ = obj.size_;
    pos_ = obj.pos_;
    if (!obj.size_) {
        flattened_tree_ = nullptr;
    } else {
        flattened_tree_ = new T[obj.size_];
        for (size_t i = 0; i < size_; i++) {
            flattened_tree_[i] = obj.flattened_tree_[i];
        }
    }
}

template<typename T>
Iterator<T>::~Iterator() {
    if (flattened_tree_) {
        delete [] flattened_tree_;
    }
}

template<typename T>
Iterator<T> &Iterator<T>::begin() {
    pos_ = 0;
    return *this;
}

template<typename T>
Iterator<T> &Iterator<T>::end() {
    pos_ = size_;
    return *this;
}

template<typename T>
bool Iterator<T>::hasNext() {
    if (!size_) {
        return false;
    }
    return pos_ <= size_ - 1;
}

template<typename T>
bool Iterator<T>::hasPrevious() {
    return pos_ > 0;
}

template<typename T>
bool Iterator<T>::isEnd() {
    return pos_ == size_;
}

template<typename T>
void Iterator<T>::next() {
    if (!hasNext()) {
        throw BSTIteratorOutOfRangeException("iterator out of range");
    }
    pos_++;
}

template<typename T>
void Iterator<T>::previous() {
    if (!hasPrevious()) {
        throw BSTIteratorOutOfRangeException("iterator out of range");
    }
    pos_--;
}

template<typename T>
T &Iterator<T>::value() {
    if (isEnd()) {
        throw BSTIteratorAccessingEndValueException("end value to access");
    }
    return flattened_tree_[pos_];
}

template<typename T>
Iterator<T> &Iterator<T>::operator+=(int offset) {
    if (pos_ + offset > size_ || pos_ + offset < 0) {
        throw BSTIteratorOutOfRangeException("iterator out of range");
    }
    pos_ += offset;
    return *this;
}

template<typename T>
Iterator<T> &Iterator<T>::operator-=(int offset) {
    if (pos_ - offset > size_ || pos_ - offset < 0) {
        throw BSTIteratorOutOfRangeException("iterator out of range");
    }
    pos_ -= offset;
    return *this;
}

template<typename T>
Iterator<T> &Iterator<T>::operator++() {
    this->next();
    return *this;
}

template<typename T>
Iterator<T> &Iterator<T>::operator--() {
    this->previous();
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator++(int) {
    Iterator<T> old(*this);
    ++(*this);
    return old;
}

template<typename T>
Iterator<T> Iterator<T>::operator--(int) {
    Iterator<T> old(*this);
    --(*this);
    return old;
}

template<typename T>
T &Iterator<T>::operator*() {
    return value();
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
        if (flattened_tree_[i] != it.flattened_tree_[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Iterator<T>::operator!=(Iterator<T> &it) {
    return !(*this == it);
}

template<typename T>
bool Iterator<T>::operator<(Iterator<T> &it) {
    return pos_ < it.pos_;
}

template<typename T>
bool Iterator<T>::operator>(Iterator<T> &it) {
    return pos_ > it.pos_;
}

template<typename T>
bool Iterator<T>::operator<=(Iterator<T> &it) {
    return *this < it or *this == it;
}

template<typename T>
bool Iterator<T>::operator>=(Iterator<T> &it) {
    return *this > it or *this == it;
}

template<typename _T>
Iterator<_T> operator+(const Iterator<_T> &obj, int offset) {
    Iterator<_T> sum(obj);
    if (obj.pos_ + offset >= obj.size_ || obj.pos_ + offset < 0) {
        throw BSTIteratorOutOfRangeException("iterator out of range");
    }
    sum.pos_ += offset;
    return sum;
}

template<typename _T>
Iterator<_T> operator-(const Iterator<_T> &obj, int offset) {
    Iterator<_T> diff(obj);
    if (obj.pos_ - offset >= obj.size_ || obj.pos_ - offset < 0) {
        throw BSTIteratorOutOfRangeException("iterator out of range");
    }
    diff.pos_ -= offset;
    return diff;
}

#endif  // CONTAINER_BINARY_SEARCH_TREE_H

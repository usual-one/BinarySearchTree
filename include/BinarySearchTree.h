#ifndef CONTAINER_BINARY_SEARCH_TREE_H
#define CONTAINER_BINARY_SEARCH_TREE_H

#include <initializer_list>
#include <ostream>
#include <functional>

#include "Iterator/InOrderIterator.h"
#include "Iterator/ReverseOrderIterator.h"
#include "Iterator/PreOrderIterator.h"
#include "Iterator/PostOrderIterator.h"

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

    void setOrder(tree_order order);
//    Смена порядка прохода по дереву

    void setComparator(std::function<int(T, T)> comparator);
//    Смена функции сравнения

    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &obj);
//    Перегрузка оператора присваивания

    size_t size();
//    Количество элементов в дереве

    bool isEmpty();
//    Проверить на пустоту

    void add(const T &elem);
//    Добавить элемент

    void addMany(const T *arr, size_t size);
//    Добавить элементы из указанного массива

    void remove(const T &elem);
//    Удалить элемент

    void removeMany(const T *arr, size_t size);
//    Удалить элементы из указанного массива

    void clear();
//    Очистить дерево (удалить все элементы)

    bool contains(const T &elem);
//    Проверить имеется ли указанный элемент в дереве

    bool contains(const BinarySearchTree<T> &obj);
//    Проверить имеется ли указанная ветка в дереве

    BinarySearchTree<T> *find(const T &elem);
//    Найти элемент со значением равным указанному

    T min();
//    Вернуть минимальный элемент

    T max();
//    Вернуть максимальный элемент

    void extend(const BinarySearchTree<T> &obj);
//    Расширить дерево, путем сложения его с данным

    friend BinarySearchTree<T>
    operator+(const BinarySearchTree<T> &obj1, const BinarySearchTree<T> &obj2);
//    Сложение с другим деревом (аналогично extend)

    BinarySearchTree<T> &operator+=(const BinarySearchTree<T> &obj);
//    Сложение с другим деревом (аналогично extend), результат сложения в this

    friend std::ostream &operator<<(std::ostream &os, const BinarySearchTree<T> &obj);
//    Вывод класса в поток

    friend bool operator==(const BinarySearchTree<T> &obj1, const BinarySearchTree<T> &obj2);

    Iterator<T> iteratorBegin();
//    Получить итератор на начало дерева

    Iterator<T> iteratorEnd();
//    Получить итератор следующий за последним

    T *toArray();
//    Конвертация дерева в массив

private:
//    bool isLeaf();
//    Проверить является ли ветка листом (имеет ли дочерние элементы)

    BinarySearchTree<T> *minElement();

    BinarySearchTree<T> *maxElement();

    static int defaultCompare(T a, T b);

    Iterator<T> createIterator();

    void dealloc();
//    освобождения памяти всей текущей ветки

    BinarySearchTree<T> *parent_;
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
    empty_ = true;
    order_ = obj.order_;
    comparator_ = obj.comparator_;
    addMany(obj.toArray(), obj.size());
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &&obj) noexcept {
    empty_ = true;
    order_ = obj.order_;
    comparator_ = obj.comparator_;
    addMany(obj.toArray(), obj.size());
    obj.BinarySearchTree();
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
void BinarySearchTree<T>::setOrder(tree_order order) {
    order_ = order;
}

template<typename T>
void BinarySearchTree<T>::setComparator(std::function<int(T, T)> comparator) {
    comparator_ = comparator;
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
size_t BinarySearchTree<T>::size() {
    size_t size = 0;
    if (empty_) {
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
bool BinarySearchTree<T>::isEmpty() {
    return empty_;
}

template<typename T>
void BinarySearchTree<T>::add(const T &elem) {
    if (empty_) {
        empty_ = false;
        value_ = elem;
        parent_ = this;
    }
    if (!comparator_(elem, value_)) {
        return;
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
    for (size_t i = 0; i < size; i++) {
        add(arr[i]);
    }
}

template<typename T>
void BinarySearchTree<T>::remove(const T &elem) {
    BinarySearchTree<T> *found = find(elem);
    if (!found) {
        return;
    }

    BinarySearchTree *successor;
    if (found->smaller_child_ && found->greater_child_) {
        if (found->smaller_child_->size() > found->greater_child_->size()) {
            successor = found->smaller_child_->maxElement();
            found->value_ = successor->value_;
            remove(successor);
        } else {
            successor = found->greater_child_->minElement();
            found->value_ = successor->value_;
            remove(successor);
        }
        return;
    }

    if (found->smaller_child_ && !found->greater_child_) {
        found->smaller_child_->parent_ = found->parent_;
        successor = found->smaller_child_;
    }
    if (found->greater_child_ && !found->smaller_child_) {
        found->greater_child_->parent_ = found->parent_;
        successor = found->greater_child_;
    }
    delete found;
    if (elem == found->parent_->smaller_child_->value_) {
        found->parent_->smaller_child_ = successor;
    } else if (elem == found->parent_->greater_child_->value_) {
        found->parent_->greater_child_ = successor;
    }

}

template<typename T>
void BinarySearchTree<T>::removeMany(const T *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        remove(arr[i]);
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
bool BinarySearchTree<T>::contains(const BinarySearchTree<T> &obj) {
    bool existence = this == obj;
    if (!existence && smaller_child_) {
        existence = smaller_child_->contains(obj);
    }
    if (!existence && greater_child_) {
        existence = greater_child_->contains(obj);
    }
    return existence;
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
T BinarySearchTree<T>::min() {
    return minElement()->value_;
}

template<typename T>
T BinarySearchTree<T>::max() {
    return maxElement()->value;
}

template<typename T>
void BinarySearchTree<T>::extend(const BinarySearchTree<T> &obj) {
    for (auto it = obj.iteratorBegin(); it < obj.iteratorEnd(); it++) {
        add(*it);
    }
}

template<typename T>
BinarySearchTree<T> operator+(const BinarySearchTree<T> &obj1, const BinarySearchTree<T> &obj2) {
    BinarySearchTree<T> sum(obj1);
    sum.extend(obj2);
    return sum;
}

template<typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator+=(const BinarySearchTree<T> &obj) {
    extend(obj);
    return this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const BinarySearchTree<T> &obj) {
    os << '{';
    for (auto it = obj.iteratorBegin(); it < obj.iteratorEnd() - 1; it++) {
        os << *it << ",";
    }
    os << *(--obj.iteratorEnd()) << "}";
    return os;
}

template<typename T>
bool operator==(const BinarySearchTree<T> &obj1, const BinarySearchTree<T> &obj2) {
    if (obj1.order_ != obj2.order_) {
        return false;
    }
    if (obj1.comparator_ != obj2.comparator_) {
        return false;
    }
    if (obj1.size() != obj2.size()) {
        return false;
    }
    if (!obj1.isEmpty()) {
        for (auto it1 = obj1.iteratorBegin(), it2 = obj2.iteratorBegin(); it1 < obj1.iteratorEnd;
             it1++, it2++) {
            if (*it1 != *it2) {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
Iterator<T> BinarySearchTree<T>::iteratorBegin() {
    auto it = createIterator();
    return it.begin();
}

template<typename T>
Iterator<T> BinarySearchTree<T>::iteratorEnd() {
    auto it = createIterator();
    return it.end();
}

template<typename T>
T *BinarySearchTree<T>::toArray() {
    T *arr = new T[size()];
    for (auto it = iteratorBegin(), i = 0; it < iteratorEnd(); it++, i++) {
        arr[i] = *it;
    }
    return arr;
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
BinarySearchTree<T> *BinarySearchTree<T>::maxElement() {
    BinarySearchTree<T> *maximum = this;
    if (greater_child_) {
        maximum = greater_child_->maxElement();
    }
    return maximum;
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
Iterator<T> BinarySearchTree<T>::createIterator() {
    Iterator<T> it;
    if (order_ == IN_ORDER) {
        it = InOrderIterator<T>(this);
    }
    if (order_ == REVERSE_ORDER) {
        it = ReverseOrderIterator<T>(this);
    }
    if (order_ == PRE_ORDER) {
        it = PreOrderIterator<T>(this);
    }
    if (order_ == POST_ORDER) {
        it = PostOrderIterator<T>(this);
    }
    return it;
}

template<typename T>
void BinarySearchTree<T>::dealloc() {
    if (smaller_child_) {
        smaller_child_->dealloc();
        delete smaller_child_;
    }
    if (greater_child_) {
        greater_child_->dealloc();
        delete greater_child_;
    }
}

#endif  // CONTAINER_BINARY_SEARCH_TREE_H

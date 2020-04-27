#ifndef CONTAINER_BINARYTREE_H
#define CONTAINER_BINARYTREE_H

#include <initializer_list>
#include <ostream>
#include <functional>

enum tree_order {
    IN_ORDER,
    REVERSE_ORDER,
    PRE_ORDER,
    POST_ORDER
};

template<typename T>
class Iterator;

template<typename T>
class BinaryTree {
public:
    explicit BinaryTree(tree_order order = IN_ORDER,
                        std::function<int(T, T)> comparator = defaultCompare);
//    Конструктор по умолчанию

    BinaryTree(const BinaryTree<T> &obj);
//    Конструктор копирования

    BinaryTree(const BinaryTree<T> &&obj) noexcept ;
//    Конструктор переноса

    BinaryTree(std::initializer_list<T> &lst, tree_order order = IN_ORDER,
               std::function<int(T, T)> comparator = defaultCompare);
//    Конструктор со списком инициализации

    ~BinaryTree();
//    Деструктор

    void setOrder(tree_order order);
//    Смена порядка прохода по дереву

    void setComparator(std::function<int(T, T)> comparator);
//    Смена функции сравнения

    BinaryTree<T> &operator=(const BinaryTree<T> &obj);
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

    void clear(const T &elem);
//    Очистить дерево (удалить все элементы)

    bool contains(const T &elem);
//    Проверить имеется ли указанный элемент в дереве

    bool contains(const BinaryTree<T> &obj);
//    Проверить имеется ли указанная ветка в дереве

    T min();
//    Вернуть минимальный элемент

    T max();
//    Вернуть максимальный элемент

    void extend(const BinaryTree<T> &obj);
//    Расширить дерево, путем сложения его с данным

    template<typename _T>
    friend BinaryTree<_T> operator+(const BinaryTree<_T> &obj1, const BinaryTree<_T> &obj2);
//    Сложение с другим деревом (аналогично extend)

    BinaryTree<T> &operator+=(const BinaryTree<T> &obj);
//    Сложение с другим деревом (аналогично extend), результат сложения в this

    template<typename _T>
    friend std::ostream &operator<<(const std::ostream &os, const BinaryTree<_T> &obj);
//    Вывод класса в поток

    Iterator<T> iterator_begin();
//    Получить итератор на начало дерева

    Iterator<T> iterator_end();
//    Получить итератор следующий за последним

    T *toArray();
//    Конвертация дерева в массив

private:
//    bool isLeaf();
//    Проверить является ли ветка листом (имеет ли дочерние элементы)

    static int defaultCompare(T a, T b);

    void dealloc();
//    освобождения памяти всей текущей ветки

    BinaryTree<T> *parent_;
    BinaryTree<T> *smaller_child_;
    BinaryTree<T> *greater_child_;
    T value_;

    bool empty_;

    tree_order order_;
    std::function<int(T, T)> comparator_;
};

template<typename T>
BinaryTree<T>::BinaryTree(tree_order order, std::function<int(T, T)> comparator) {
    parent_ = nullptr;
    smaller_child_ = nullptr;
    greater_child_ = nullptr;
    value_ = 0;
    empty_ = true;
    order_ = order;
    comparator_ = comparator;
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &obj) {
    empty_ = true;
    order_ = obj.order_;
    comparator_ = obj.comparator_;
    addMany(obj.toArray(), obj.size());
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &&obj) noexcept {
    empty_ = true;
    order_ = obj.order_;
    comparator_ = obj.comparator_;
    addMany(obj.toArray(), obj.size());
    obj.~BinaryTree();
}

template<typename T>
BinaryTree<T>::BinaryTree(std::initializer_list<T> &lst, tree_order order,
                          std::function<int(T, T)> comparator) {
    empty_ = true;
    order_ = order;
    comparator_ = comparator;
    for (auto el : lst) {
        add(el);
    }
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    dealloc();
}

template<typename T>
void BinaryTree<T>::setOrder(tree_order order) {
    order_ = order;
}

template<typename T>
void BinaryTree<T>::setComparator(std::function<int(T, T)> comparator) {
    comparator_ = comparator;
}

template<typename T>
size_t BinaryTree<T>::size() {
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
bool BinaryTree<T>::isEmpty() {
    return empty_;
}

template<typename T>
void BinaryTree<T>::add(const T &elem) {
    if (empty_) {
        empty_ = false;
        value_ = elem;
    }
    if (!comparator_(elem, value_)) {
        return;
    }
    if (comparator_(elem, value_) < 0) {
        if (!smaller_child_) {
            smaller_child_ = new BinaryTree(order_, comparator_);
        }
        smaller_child_->add(elem);
    } else {
        if (!greater_child_) {
            greater_child_ = new BinaryTree(order_, comparator_);
        }
        greater_child_->add(elem);
    }
}

template<typename T>
void BinaryTree<T>::addMany(const T *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        add(arr[i]);
    }
}

template<typename T>
T BinaryTree<T>::min() {
    T minimum = value_;
    if (smaller_child_) {
        minimum = smaller_child_->min();
    }
    return minimum;
}

template<typename T>
T BinaryTree<T>::max() {
    T maximum = value_;
    if (greater_child_) {
        maximum = greater_child_->max();
    }
    return maximum;
}

template<typename T>
int BinaryTree<T>::defaultCompare(T a, T b) {
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}

template<typename T>
void BinaryTree<T>::dealloc() {
    if (smaller_child_) {
        smaller_child_->dealloc();
        delete smaller_child_;
    }
    if (greater_child_) {
        greater_child_->dealloc();
        delete greater_child_;
    }
}

#endif // CONTAINER_BINARYTREE_H

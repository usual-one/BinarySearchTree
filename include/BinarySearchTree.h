#ifndef CONTAINER_BINARY_SEARCH_TREE_H
#define CONTAINER_BINARY_SEARCH_TREE_H

#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <memory>
#include <ostream>

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

    size_t size() const;
//    Количество элементов в дереве

    bool isEmpty() const;
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

    bool contains(const T &elem) const;
//    Проверить имеется ли указанный элемент в дереве

    bool contains(const BinarySearchTree<T> &obj) const;
//    Проверить имеется ли указанная ветка в дереве

    T min() const;
//    Вернуть минимальный элемент

    T max() const;
//    Вернуть максимальный элемент

    void extend(const BinarySearchTree<T> &obj);
//    Расширить дерево, путем сложения его с данным

    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &obj);
//    Перегрузка оператора присваивания

    template<typename _T>
    friend BinarySearchTree<_T>
    operator+(const BinarySearchTree<_T> &obj1, const BinarySearchTree<_T> &obj2);
//    Сложение с другим деревом (аналогично extend)

    BinarySearchTree<T> &operator+=(const BinarySearchTree<T> &obj);
//    Сложение с другим деревом (аналогично extend), результат сложения в this

    template<typename _T>
    friend std::ostream &operator<<(std::ostream &os, const BinarySearchTree<_T> &obj);
//    Перегрузка оператора вывода на поток

    template<typename _T>
    friend bool operator==(const BinarySearchTree<_T> &obj1, const BinarySearchTree<_T> &obj2);
//    Перегрузка оператора равенства

    Iterator<T> *iteratorBegin() const;
//    Получить итератор на начало дерева

    Iterator<T> *iteratorEnd() const;
//    Получить итератор на фиктивный элемент, следующий за последним

    T *toArray() const;
//    Конвертировать ветку в массив

private:
    BinarySearchTree<T> *find(const T &elem) const;
//    Найти элемент со значением равным указанному

    BinarySearchTree<T> *minElement() const;
//    Найти элемент с минимальным значением

    BinarySearchTree<T> *maxElement() const;
//    Найти элемент с максимальным значением

    static int defaultCompare(T a, T b);
//    Функция сравнения элементов по умолчанию

    void addToArray(T *arr, size_t *current_size) const;
//    Добавить ветку в массив

    void dealloc();
//    Освободить память всей текущей ветки

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
void BinarySearchTree<T>::setOrder(tree_order order) {
    order_ = order;
}

template<typename T>
void BinarySearchTree<T>::setComparator(std::function<int(T, T)> comparator) {
    comparator_ = comparator;
}

template<typename T>
size_t BinarySearchTree<T>::size() const {
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
bool BinarySearchTree<T>::isEmpty() const {
    return empty_;
}

template<typename T>
void BinarySearchTree<T>::add(const T &elem) {
    if (empty_) {
        empty_ = false;
        value_ = elem;
        if (!parent_) {
            parent_ = this;
        }
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
bool BinarySearchTree<T>::contains(const T &elem) const {
    return (bool) find(elem);
}

template<typename T>
bool BinarySearchTree<T>::contains(const BinarySearchTree<T> &obj) const {
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
BinarySearchTree<T> *BinarySearchTree<T>::find(const T &elem) const {
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
T BinarySearchTree<T>::min() const {
    return minElement()->value_;
}

template<typename T>
T BinarySearchTree<T>::max() const {
    return maxElement()->value;
}

template<typename T>
void BinarySearchTree<T>::extend(const BinarySearchTree<T> &obj) {
    for (auto it = obj.iteratorBegin(); it < obj.iteratorEnd(); it++) {
        add(*it);
    }
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

template<typename _T>
BinarySearchTree<_T> operator+(const BinarySearchTree<_T> &obj1, const BinarySearchTree<_T> &obj2) {
    BinarySearchTree<_T> sum(obj1);
    sum.extend(obj2);
    return sum;
}

template<typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator+=(const BinarySearchTree<T> &obj) {
    extend(obj);
    return this;
}

template<typename _T>
std::ostream &operator<<(std::ostream &os, const BinarySearchTree<_T> &obj) {
    os << "{";
    auto it_begin = *obj.iteratorBegin();
    auto it_end = --(*obj.iteratorEnd());
    for (auto it = it_begin; it < it_end; it++) {
        os << *it << ", ";
    }
    os << *it_end << "}";
    return os;
}

template<typename _T>
bool operator==(const BinarySearchTree<_T> &obj1, const BinarySearchTree<_T> &obj2) {
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
Iterator<T> *BinarySearchTree<T>::iteratorBegin() const {
    auto it = new Iterator<T>(*this);
    it->begin();
    return it;
}

template<typename T>
Iterator<T> *BinarySearchTree<T>::iteratorEnd() const {
    auto it = new Iterator<T>(*this);
    it->end();
    return it;
}

template<typename T>
T *BinarySearchTree<T>::toArray() const {
    T *arr = new T[size()];
    size_t arr_size = 0;
    addToArray(arr, &arr_size);
    return arr;
}

template<typename T>
void BinarySearchTree<T>::addToArray(T *arr, size_t *current_size) const {
    if (empty_) {
        return;
    }
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
BinarySearchTree<T> *BinarySearchTree<T>::minElement() const {
    BinarySearchTree<T> *minimum = this;
    if (smaller_child_) {
        minimum = smaller_child_->minElement();
    }
    return minimum;
}

template<typename T>
BinarySearchTree<T> *BinarySearchTree<T>::maxElement() const {
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



template<typename T>
class Iterator {
public:
    Iterator() = delete;
//    Конструктор по умолчанию (удален)

    explicit Iterator(const BinarySearchTree<T> &tree);
//    Конструктор

    Iterator(const Iterator<T> &obj);

    ~Iterator();
//    Деструктор

    Iterator<T> &begin();
//    Получить итератор на первый элемент

    Iterator<T> &end();
//    Получить итератор на фиктивный элемент, следующий за последним

    bool is_end();
//    Находится ли итератор наа фиктивном элементе, следующем за последним

    bool hasNext();
//    Имеет ли итератор следующий элемент (в т. ч. фиктивный)

    bool hasPrevious();
//    Имеет ли итератор предыдущий элемент

    void next();
//    Сместиться на следующий элемент

    void previous();
//    Сместиться на предыдущий элемент

    T value();
//    Получить значение текущего элемента

    template<typename _T>
    friend Iterator<_T> &operator+(const Iterator<_T> &obj, int offset);
//    Вернуть итератор, смещенный на offset позиций вперед

    template<typename _T>
    friend Iterator<_T> &operator-(const Iterator<_T> &obj, int offset);
//    Вернуть итератор, смещенный на offset позиций назад

    Iterator<T> &operator+=(int offset);
//    Сместить текущий итератор на offset позиций вперед

    Iterator<T> &operator-=(int offset);
//    Сместить текущий итератор на offset позиций назад

    Iterator<T> &operator++();

    Iterator<T> &operator--();

    Iterator<T> &operator++(int);

    Iterator<T> &operator--(int);

    T &operator*();

    bool operator==(Iterator<T> &it);

    bool operator!=(Iterator<T> &it);

    bool operator<(Iterator<T> &it);

    bool operator>(Iterator<T> &it);

    bool operator<=(Iterator<T> &it);

    bool operator>=(Iterator<T> &it);

private:
    T *flattened_tree_;
    size_t size_;
    size_t pos_;
};

template<typename T>
Iterator<T>::Iterator(const BinarySearchTree<T> &tree) {
    flattened_tree_ = tree.toArray();
    size_ = tree.size();
    pos_ = 0;
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T> &obj) {
    size_ = obj.size_;
    pos_ = obj.pos_;
    flattened_tree_ = new T[obj.size_];
    for (size_t i = 0; i < size_; i++) {
        flattened_tree_[i] = obj.flattened_tree_[i];
    }
}

template<typename T>
Iterator<T>::~Iterator() {
    delete [] flattened_tree_;
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
bool Iterator<T>::is_end() {
    return pos_ == size_;
}

template<typename T>
bool Iterator<T>::hasNext() {
    return pos_ <= size_ - 1;
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
        pos_--;
    }
}

template<typename T>
T Iterator<T>::value() {
    return flattened_tree_[pos_];
}

template<typename _T>
Iterator<_T> &operator+(const Iterator<_T> &obj, int offset) {
    Iterator<_T> sum(obj);
    if (obj.pos_ + offset < obj.size_) {
        sum.pos_ += offset;
    }
    return sum;
}

template<typename _T>
Iterator<_T> &operator-(const Iterator<_T> &obj, int offset) {
    Iterator<_T> diff(obj);
    if (obj.pos_ - offset >= 0) {
        diff.pos_ -= offset;
    }
    return diff;
}

template<typename T>
Iterator<T> &Iterator<T>::operator+=(int offset) {
    if (pos_ + offset < size_) {
        pos_ += offset;
    }
    return this;
}

template<typename T>
Iterator<T> &Iterator<T>::operator-=(int offset) {
    if (pos_ - offset >= 0) {
        pos_ -= offset;
    }
    return this;
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
Iterator<T> &Iterator<T>::operator++(int) {
    Iterator<T> old(*this);
    ++(*this);
    return old;
}

template<typename T>
Iterator<T> &Iterator<T>::operator--(int) {
    Iterator<T> old(*this);
    --(*this);
    return old;
}

template<typename T>
T &Iterator<T>::operator*() {
    return flattened_tree_[pos_];
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

#endif  // CONTAINER_BINARY_SEARCH_TREE_H

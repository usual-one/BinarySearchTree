## Interface documentation
#### BinarySearchTree


Default constructor.
```c++
explicit BinarySearchTree(tree_order order = IN_ORDER, std::function<int(T, T)> comparator = defaultCompare);
```


Copy constructor.
```c++
BinarySearchTree(const BinarySearchTree<T> &obj);
```


Move constructor.
```c++
BinarySearchTree(const BinarySearchTree<T> &&obj) noexcept;
```


Constructor with initializer list.
```c++
BinarySearchTree(std::initializer_list<T> &lst, tree_order order = IN_ORDER, std::function<int(T, T)> comparator = defaultCompare);
```


Destructor.
```c++
~BinarySearchTree() noexcept;
```


Sets traversal order.
```c++
void setOrder(tree_order order);
```


Sets comparator that compares values of type T.
```c++
void setComparator(std::function<int(T, T)> comparator);
```


Gets number of elements in the tree.
```c++
size_t size() const;
```


Checks if number of elements is zero.
```c++
bool isEmpty() const;
```


Adds new element.

May throw `BSTDuplicateValueException` if element already exists in the tree.
```c++
void add(const T &elem);
```


Adds new elements from given array.

May throw `BSTDuplicateValueException` if some elements already exist in the tree.
```c++
void addMany(const T *arr, size_t size);
```


Removes element.

May throw `BSTNonexistentValueException` if no element equal to `elem` was found.
```c++
void remove(const T &elem);
```
    

Removes elements from given array.

May throw `BSTNonexistentValueException` if some elements were not found.
```c++
void removeMany(const T *arr, size_t size);
```


Removes every element from the tree.
```c++
void clear();
```
    
    
Checks if tree contains given element.
```c++
bool contains(const T &elem) const;
```


Checks if given tree is a subtree.

May throw `BSTEmptyException` if given tree is empty.
```c++
bool contains(const BinarySearchTree<T> &obj) const;
```


Gets minimal element.

May throw `BSTEmptyException` if tree is empty.
```c++
T min() const;
```


Gets maximal element.

May throw `BSTEmptyException` if tree is empty.
```c++
T max() const;
```


Extend tree by adding given tree in its order.

May throw `BSTEmptyException` if given tree is empty.
```c++
void extend(const BinarySearchTree<T> &obj);
```


Convert the tree to array.

May throw `BSTEmptyException` if tree is empty.
```c++
T *toArray() const;
```


Gets iterator for the first element.
```c++
Iterator<T> *iteratorBegin() const;
```
    

Gets iterator for the element next for last one.
```c++
Iterator<T> *iteratorEnd() const;
```


Assigment operator overload.
```c++
BinarySearchTree<T> &operator=(const BinarySearchTree<T> &obj);
```


Addition operator overload.
```c++
template<typename _T>
friend BinarySearchTree<_T> operator+(const BinarySearchTree<_T> &obj1, const BinarySearchTree<_T> &obj2);
```


Addition & assigment operator overload (same as `extend`).
```c++
BinarySearchTree<T> &operator+=(const BinarySearchTree<T> &obj);
```


Stream output operator overload.
```c++
template<typename _T>
friend std::ostream &operator<<(std::ostream &os, const BinarySearchTree<_T> &obj);
```


Equality operator overload.
```c++
template<typename _T>
friend bool operator==(const BinarySearchTree<_T> &obj1, const BinarySearchTree<_T> &obj2);
```

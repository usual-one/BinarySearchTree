## Interface documentation
#### Iterator


Default constructor is deleted.
```c++
Iterator() = delete;
```


Constructor overload.
```c++
explicit Iterator(const BinarySearchTree<T> &tree);
```


Copy constructor.
```c++
Iterator(const Iterator<T> &obj);
```
    

Destructor.
```c++
~Iterator();
```


Sets and returns iterator for the first element.
```c++
Iterator<T> &begin();
```
    

Sets and returns iterator for the element next for last one.
```c++
Iterator<T> &end();
```


Checks if iterator is on the end position.
```c++
bool is_end();
```
    

Checks if element next for current exists (end element counts).
```c++
bool hasNext();
```


Checks if element previous for current exists.
```c++
bool hasPrevious();
```


Sets iterator position to next element.

May throw `BSTIteratorOutOfRangeException` if next element is nonexistent.
```c++
void next();
```


Sets iterator position to previous element.

May throw `BSTIteratorOutOfRangeException` if previous element is nonexistent.
```c++
void previous();
```


Gets current element value.

May throw `BSTIteratorAccessingEndValueException` if element is end element.
```c++
T &value();
```


Addition operator overload.
```c++
template<typename _T>
friend Iterator<_T> &operator+(const Iterator<_T> &obj, int offset);
```


Subtraction operator overload.
```c++
template<typename _T>
friend Iterator<_T> &operator-(const Iterator<_T> &obj, int offset);
```


Addition & assigment operator overload.
```c++
Iterator<T> &operator+=(int offset);
```


Subtraction & assigment operator overload.
```c++
Iterator<T> &operator-=(int offset);
```

   
Prefix increment operator overload.
```c++
Iterator<T> &operator++();
```


Prefix decrement operator overload.
```c++
Iterator<T> &operator--();
```


Postfix increment operator overload.
```c++
Iterator<T> &operator++(int);
```


Postfix decrement operator overload.
```c++
Iterator<T> &operator--(int);
```


Dereferencing operator overload.
```c++
T &operator*();
```


Equality operator overload.
```c++
bool operator==(Iterator<T> &it);
```


Inequality operator overload.
```c++
bool operator!=(Iterator<T> &it);
```


Less operator overload.
```c++
bool operator<(Iterator<T> &it);
```


Greater operator overload.
```c++
bool operator>(Iterator<T> &it);
```


Less or equal operator overload.
```c++
bool operator<=(Iterator<T> &it);
```


Greater or equal operator overload.
```c++
bool operator>=(Iterator<T> &it);
```

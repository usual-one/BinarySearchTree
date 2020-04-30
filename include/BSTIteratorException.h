#ifndef CONTAINER_BSTITERATOREXCEPTION_H
#define CONTAINER_BSTITERATOREXCEPTION_H


#include "BSTException.h"

class BSTIteratorException : public BSTException {
public:
    BSTIteratorException();

    explicit BSTIteratorException(const std::string &msg);
};

class BSTIteratorOutOfRangeException : public BSTIteratorException {
public:
    BSTIteratorOutOfRangeException()
            : BSTIteratorException() {}

    explicit BSTIteratorOutOfRangeException(const std::string &msg)
            : BSTIteratorException("BSTIteratorOutOfRangeException: " + msg) {}
};

class BSTIteratorAccessingEndValueException : public BSTIteratorException {
public:
    BSTIteratorAccessingEndValueException()
            : BSTIteratorException() {}

    explicit BSTIteratorAccessingEndValueException(const std::string &msg)
            : BSTIteratorException("BSTIteratorAccessingEndValueException: " + msg) {}
};

#endif //CONTAINER_BSTITERATOREXCEPTION_H

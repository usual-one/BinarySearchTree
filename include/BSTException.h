#ifndef CONTAINER_BSTEXCEPTION_H
#define CONTAINER_BSTEXCEPTION_H

#include <exception>
#include <string>

class BSTException : public std::exception {
public:
    BSTException();

    explicit BSTException(const std::string &msg);

    const char *what() const noexcept override;

protected:
    std::string msg_;
};

class BSTDuplicateValueException : public BSTException {
public:
    BSTDuplicateValueException()
            : BSTException() {}

    explicit BSTDuplicateValueException(const std::string &msg)
            : BSTException("BSTDuplicateValueException: " + msg) {}
};

class BSTNonexistentValueException : public BSTException {
public:
    BSTNonexistentValueException()
            : BSTException() {}

    explicit BSTNonexistentValueException(const std::string &msg)
            : BSTException("BSTNonexistentValueException: " + msg) {}
};

class BSTEmptyException : public BSTException {
public:
    BSTEmptyException()
            : BSTException() {}

    explicit BSTEmptyException(const std::string &msg)
            : BSTException("BSTEmptyException: " + msg) {}
};

#endif //CONTAINER_BSTEXCEPTION_H

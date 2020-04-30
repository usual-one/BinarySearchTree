#include "BSTIteratorException.h"

BSTIteratorException::BSTIteratorException() {
    msg_ = "BSTIteratorException";
}

BSTIteratorException::BSTIteratorException(const std::string &msg) {
    msg_ = "BSTIteratorException: " + msg;
}

#include "BSTException.h"

BSTException::BSTException() {
    msg_ = "BSTException";
}

BSTException::BSTException(const std::string &msg) {
    msg_ = "BSTException: " + msg;
}

const char *BSTException::what() const noexcept {
    return msg_.data();
}

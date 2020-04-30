cmake_minimum_required(VERSION 3.16)
project(Container)

set(CMAKE_CXX_STANDARD 17)

add_library(BinarySearchTree SHARED
        src/BinarySearchTree.cpp
        src/BSTException.cpp
        src/BSTIteratorException.cpp)
target_include_directories(BinarySearchTree PUBLIC include)

add_executable(Container main.cpp)
target_link_libraries(Container PUBLIC BinarySearchTree)
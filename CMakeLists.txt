cmake_minimum_required(VERSION 3.16)
project(Container)

set(CMAKE_CXX_STANDARD 17)

add_library(BinaryTree SHARED
        src/BinarySearchTree.cpp
        src/Iterator/Iterator.cpp
        src/Iterator/InOrderIterator.cpp
        src/Iterator/PreOrderIterator.cpp
        src/Iterator/PostOrderIterator.cpp src/Iterator/ReverseOrderIterator.cpp)
target_include_directories(BinaryTree PUBLIC include)

add_executable(Container main.cpp)
target_link_libraries(Container PUBLIC BinaryTree)
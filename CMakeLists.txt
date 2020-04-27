cmake_minimum_required(VERSION 3.16)
project(Container)

set(CMAKE_CXX_STANDARD 17)

add_library(BinaryTree SHARED
        src/BinaryTree.cpp
        src/Iterator.cpp
        src/InorderIterator.cpp
        src/PreorderIterator.cpp
        src/PostorderIterator.cpp)
target_include_directories(BinaryTree PUBLIC include)

add_executable(Container main.cpp)
target_link_libraries(Container PUBLIC BinaryTree)
cmake_minimum_required(VERSION 3.2)
project(my_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(my_project main.cpp
    BinaryTree.cpp
        BinaryTree.h
        Token.cpp
        Token.h
        AVL.cpp
        AVL.h
        TokenLRpointer.cpp
        TokenLRpointer.h)

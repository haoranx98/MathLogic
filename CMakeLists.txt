cmake_minimum_required(VERSION 3.23)
project(MathLogic)

set(CMAKE_CXX_STANDARD 14)

add_executable(MathLogic main.cpp TreeNode.cpp TreeNode.h preprocess.cpp preprocess.h expression_process.cpp expression_process.h)

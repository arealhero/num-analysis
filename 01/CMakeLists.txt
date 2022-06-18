cmake_minimum_required(VERSION 3.0)

project(fun_eval)

set(CXX_STANDARD 17)

add_executable(fun_eval src/fun_eval.cc)
target_include_directories(fun_eval PUBLIC include)


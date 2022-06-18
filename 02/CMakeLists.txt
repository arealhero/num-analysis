cmake_minimum_required(VERSION 3.0)

project(sle)

set(CXX_STANDARD 17)

add_executable(sle src/sle.cc
    src/Uni/Matrix.cc
    src/Uni/Methods/GaussMethod.cc
    src/Uni/Methods/SeidelMethod.cc
)

target_include_directories(sle PUBLIC include)


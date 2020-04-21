cmake_minimum_required(VERSION 3.15)
project(tp2)

set(CMAKE_CXX_STANDARD 11)

add_executable(tp2 main.cpp)
add_subdirectory(tp2L)
add_subdirectory(tests)

add_dependencies(tp2 tp2L)

target_include_directories(tp2 PRIVATE tp2L)

target_compile_options (tp2 PRIVATE -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline)
target_link_options(tp2 PRIVATE -pthread -lm)

find_library(TP2_LIBRARY NAMES tp2L PATHS cmake-build-debug/tp2L)
target_link_libraries(tp2 LINK_PUBLIC ${TP2_LIBRARY})
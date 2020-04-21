cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_executable(tp2Tests ${SOURCES})
add_dependencies(tp2Tests tp2)

target_include_directories(tp2Tests PRIVATE ../tp2L)

target_compile_options (tp2Tests PRIVATE -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline)
target_link_options(tp2Tests PRIVATE -pthread -lm)

find_library(TP2_LIBRARY NAMES tp2L PATHS ../tp2L)
target_link_libraries(tp2Tests LINK_PUBLIC ${TP2_LIBRARY})

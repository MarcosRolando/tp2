cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(tp2L ${SOURCES})

target_compile_options (tp2L PRIVATE -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline)
target_link_options(tp2L PRIVATE -pthread -lm)

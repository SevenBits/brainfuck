cmake_minimum_required(VERSION 2.6)

project(brainfuck C)
set(VERSION_MAJOR 3)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# definitions
add_definitions("-W -Wall -Werror")
add_definitions("-std=c89")
add_definitions("-O1")
add_definitions("-fno-exceptions")
add_definitions("-fstack-protector -Wformat-security")
add_definitions("-DNO_JIT -g")

add_library(libbrainfuck STATIC src/brainfuck.c src/base.c src/list.c src/helper.c)
set_target_properties(libbrainfuck PROPERTIES PREFIX "")

add_executable(brainfuck src/main.c)
target_link_libraries(brainfuck libbrainfuck)

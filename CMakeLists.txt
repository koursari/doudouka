cmake_minimum_required(VERSION 3.12)
project(SimpleServer LANGUAGES C)

set(PORT 8080)

set(CMAKE_C_STANDARD 99)

add_compile_definitions(PORTNO=${PORT})

add_executable(${PROJECT_NAME} source/main.c)
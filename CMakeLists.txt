cmake_minimum_required(VERSION "3.26.4")

project("bfcpp")

set(PROJECT_SRC
    src/bf.cpp
    src/bf.h
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)

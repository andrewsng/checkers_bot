cmake_minimum_required(VERSION 3.14)
project("CHECKERS")

set(CMAKE_CXX_STANDARD 17)

set (SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/SFML-2.5.1/build")

find_package (SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
add_subdirectory(src)
add_subdirectory(test)

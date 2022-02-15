add_executable(CheckersTests testmain.cpp testcheckers.cpp)
target_include_directories(CheckersTests PRIVATE ${CHECKERS_SOURCE_DIR}/src)
target_link_libraries(CheckersTests Checkers)

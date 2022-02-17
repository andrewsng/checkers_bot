add_library(Checkers 
    board.cpp board.hpp
    move.cpp move.hpp
    movegen.cpp movegen.hpp
    checkersgame.cpp checkersgame.hpp
    searching.cpp searching.hpp
)
target_link_libraries(Checkers sfml-graphics)

add_executable(CheckersBot main.cpp)
target_link_libraries(CheckersBot Checkers)

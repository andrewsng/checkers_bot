add_library(Checkers 
    board.cpp board.hpp
    move.cpp move.hpp
    movegen.cpp movegen.hpp
    checkersgame.cpp checkersgame.hpp
    checkersdisplay.cpp checkersdisplay.hpp
    searching.cpp searching.hpp
    mctsnode.cpp mctsnode.hpp
    layer.hpp layer.cpp
    network.hpp network.cpp
    initializer.hpp initializer.cpp
)
target_link_libraries(Checkers sfml-graphics)

add_executable(CheckersBot main.cpp)
target_link_libraries(CheckersBot Checkers)

add_executable(NeuralNetworks nnmain.cpp)
target_link_libraries(NeuralNetworks Checkers)

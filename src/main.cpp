#include "board.hpp"
#include "movegen.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
    Board b;
    for (auto t : b.getBlackPositions()) {
        std::cout << t;
    }
    std::cout << "\n";
    auto moves = generateMoves(b, 1);
    return 0;
}

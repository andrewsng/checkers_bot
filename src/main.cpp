#include "board.hpp"
#include "movegen.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
    Board b;
    std::cout << "Black positions:\n";
    for (auto t : b.getBlackPositions()) {
        std::cout << t << ", ";
    }
    std::cout << "\n";
    auto blackMoves = generateMoves(b, 1);
    for (auto move : blackMoves) {
        std::cout << move.getStart() << " -> " << move.getEnd() << ", ";
    }
    std::cout << "\n\n";
    std::cout << "Red positions:\n";
    for (auto t : b.getRedPositions()) {
        std::cout << t << ", ";
    }
    std::cout << "\n";
    auto redMoves = generateMoves(b, 0);
    for (auto move : redMoves) {
        std::cout << move.getStart() << " -> " << move.getEnd() << ", ";
    }
    std::cout << "\n";
    return 0;
}

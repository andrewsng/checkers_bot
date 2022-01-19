#include "checkersgame.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
    CheckersGame game{};
    while (true) {
        game.printBoard();
        game.printRedMoves();
        std::cout << "\n";
        game.printBlackMoves();
        std::cout << "\n";
        Move::Tile t0, t1, t2;
        std::cin >> t0 >> t1 >> t2;
        game.makeMove(Move{t0, t1, t2});
    }
    return 0;
}

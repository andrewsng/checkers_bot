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
        while (true) {
            Move::Tile t0{};
            Move::Tile t1{};
            std::cin >> t0 >> t1;
            if (game.makeMove(Move{t0, t1, game.getTurn()})) {
                game.changeTurn();
                break;
            }
            std::cout << "Illegal Move.\n";
        }
    }
    return 0;
}

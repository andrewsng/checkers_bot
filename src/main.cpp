#include "checkersgame.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
    CheckersGame game{};
    while (true) {
        while (true) {
            game.printBoard();
            game.printRedMoves();
            std::cout << "\n";
            game.printBlackMoves();
            std::cout << "\n";
            Move::Tile t0{};
            Move::Tile t1{};
            std::cin >> t0 >> t1;
            if (auto cont = game.makeMove(Move{t0, t1, game.getTurn()})) {
                if (*cont) {
                    continue;
                }
                game.changeTurn();
                break;
            }
            std::cout << "Illegal Move.\n";
        }
    }
    return 0;
}

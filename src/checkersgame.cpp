#include "checkersgame.hpp"
#include "movegen.hpp"
#include <iostream>


void CheckersGame::printBoard() const {
    for (int y = 7; y >= 0; --y) {
        for (int x = 0; x < 8; ++x) {
            if (x % 2 == y % 2) {
                Board::Tile tile = (x + y * 8) / 2;
                std::cout << _board.symbolOn(tile);
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

void CheckersGame::printRedMoves() const {
    auto redMoves = generateMoves(_board, 0);
    for (auto move : redMoves) {
        std::cout << move.getStart() << " -> " << move.getEnd() << ", ";
    }
}

void CheckersGame::printBlackMoves() const {
    auto blackMoves = generateMoves(_board, 1);
    for (auto move : blackMoves) {
        std::cout << move.getStart() << " -> " << move.getEnd() << ", ";
    }
}

void CheckersGame::changeTurn() {
    _player = 1 - _player;
}

bool CheckersGame::makeMove(Move move) {
    auto legalMoves = generateMoves(_board, _player);
    if (std::find(legalMoves.begin(), legalMoves.end(), move) == legalMoves.end()) {
        return false;
    }
    _board.updateBoard(move);
    return true;
}

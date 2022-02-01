#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"
#include "move.hpp"
#include <optional>


class CheckersGame {

public:

    int getTurn() const { return _player; }
    void printBoard() const;
    void printRedMoves() const;
    void printBlackMoves() const;
    void changeTurn();
    std::optional<bool> makeMove(Move move);

private:

    Board _board{};
    int _player{0};

};


#endif  // CHECKERSGAME_HPP

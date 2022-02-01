#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"
#include "move.hpp"


class CheckersGame {

public:

    int getTurn() const { return _player; }
    void printBoard() const;
    void printRedMoves() const;
    void printBlackMoves() const;
    void changeTurn();
    bool makeMove(Move move);

private:

    Board _board{};
    int _player{0};

};


#endif  // CHECKERSGAME_HPP

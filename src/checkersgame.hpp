#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"
#include "move.hpp"


class CheckersGame {

public:

    void printBoard() const;
    void printRedMoves() const;
    void printBlackMoves() const;
    void makeMove(Move move);

private:

    Board _board{};

};


#endif  // CHECKERSGAME_HPP

#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"


class CheckersGame {

public:

    void makeMove(Move move);

private:

    Board _board{};

};


#endif  // CHECKERSGAME_HPP

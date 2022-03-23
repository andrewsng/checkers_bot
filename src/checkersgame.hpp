#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"


enum class PlayerType {
    Human,
    MiniMax,
    AlphaBeta
};

class CheckersGame {

public:

    void setRedPlayer(PlayerType type);
    void setBlackPlayer(PlayerType type);
    void runGame();

private:

    Board _board{};

};


#endif  // CHECKERSGAME_HPP

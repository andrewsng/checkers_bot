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
    void attemptMove();

private:

    void changeTurn();

    Board _board{};
    int _currPlayer;
    PlayerType _redPlayerType{PlayerType::Human};
    PlayerType _blackPlayerType{PlayerType::Human};

};


#endif  // CHECKERSGAME_HPP

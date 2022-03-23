#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"
#include "checkersdisplay.hpp"


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

    std::optional<Move> getMoveIfLegal(Board::Tile prevSelected,
                                       Board::Tile currSelected) const;
    bool isOver() const;

    void changeTurn();
    void displayBoard();
    void handleInputs();

    Board _board{};
    CheckersDisplay _display{1000, 1000, "Checkers"};
    int _currPlayer{0};
    PlayerType _redPlayerType{PlayerType::Human};
    PlayerType _blackPlayerType{PlayerType::Human};

};


#endif  // CHECKERSGAME_HPP

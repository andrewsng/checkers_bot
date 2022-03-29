#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"
#include "checkersdisplay.hpp"
#include <string>
#include <memory>


enum class PlayerType {
    Human,
    MiniMax,
    AlphaBeta
};

class CheckersGame {

public:

    void setRedPlayer(PlayerType type);
    void setBlackPlayer(PlayerType type);
    void createDisplay();
    void runGame();
    void attemptMove();

private:

    std::optional<Move> getMoveIfLegal(Board::Tile prevSelected,
                                       Board::Tile currSelected) const;
    bool isOver() const;

    void changeTurn();
    void displayBoard();
    void handleInputs();
    void resetDisplay(const Move &prevMove);

    Board _board{};
    int _currPlayer{0};
    PlayerType _redPlayerType{PlayerType::Human};
    PlayerType _blackPlayerType{PlayerType::Human};
    std::unique_ptr<CheckersDisplay> _display{};//{1000, 1000, "Checkers"};

};


#endif  // CHECKERSGAME_HPP

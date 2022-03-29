#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"
#include "checkersdisplay.hpp"
#include <string>
#include <memory>


enum class PlayerType {
    Human,
    Random,
    MiniMax,
    AlphaBeta
};

class CheckersGame {

public:

    CheckersGame() = default;
    CheckersGame(Board board, int currPlayer);
    void setRedPlayer(PlayerType type);
    void setBlackPlayer(PlayerType type);
    void createDisplay();
    void runGame();
    void attemptMove();
    int result() const;

private:

    bool isGameOver() const;
    bool isDisplayOpen() const;
    std::optional<Move> getMoveIfLegal(Board::Tile prevSelected,
                                       Board::Tile currSelected) const;
    std::optional<Move> getRandomMove() const;

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

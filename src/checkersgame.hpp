#ifndef CHECKERSGAME_HPP
#define CHECKERSGAME_HPP

#include "board.hpp"
#include "checkersdisplay.hpp"
#include <vector>
#include <string>
#include <memory>
#include <utility>


enum class PlayerType {
    Human,
    Random,
    MiniMax,
    AlphaBeta,
    MCTS
};

enum class GameResult {
    RedWin,
    BlackWin,
    Draw,
};

class CheckersGame {

public:

    CheckersGame() = default;
    CheckersGame(Board board, int currPlayer);
    void setRedPlayer(PlayerType type);
    void setBlackPlayer(PlayerType type);
    void createDisplay();
    void threeMoveStart();
    void runGame();
    void attemptMove();
    GameResult result() const;

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
    std::vector<std::pair<Move, int>> _moveHistory{};

};


#endif  // CHECKERSGAME_HPP

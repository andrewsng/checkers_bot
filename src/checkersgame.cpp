#include "checkersgame.hpp"
#include "move.hpp"


void CheckersGame::setRedPlayer(PlayerType type)
{}

void CheckersGame::setBlackPlayer(PlayerType type)
{}

void CheckersGame::runGame() {
    displayBoard();
    while (!isOver()) {
        handleInputs();
        attemptMove();
        displayBoard();
    }
}

void CheckersGame::attemptMove() {
    auto currPlayerType = (_currPlayer == 0) ? _redPlayerType
                                             : _blackPlayerType;
    Move moveToMake{};
    switch (currPlayerType) {
        case PlayerType::Human:
            moveToMake = getHumanMove();
            break;
        case PlayerType::MiniMax:
            moveToMake = getMiniMaxMove();
            break;
        case PlayerType::AlphaBeta:
            moveToMake = getAlphaBetaMove();
            break;
    }
    _board.makeMove(moveToMake, _currPlayer);
    changeTurn();
}

void CheckersGame::changeTurn() {
    _currPlayer = 1 - _currPlayer;
}

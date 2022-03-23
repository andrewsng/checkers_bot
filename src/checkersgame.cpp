#include "checkersgame.hpp"
#include "move.hpp"
#include "movegen.hpp"
#include <optional>
using std::optional;


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
    optional<Move> potentialMove{};
    switch (currPlayerType) {
        case PlayerType::Human:
            potentialMove = getMoveIfLegal(_display.getPrevSelected(),
                                           _display.getCurrSelected());
            break;
        /* case PlayerType::MiniMax:
            potentialMove = getMiniMaxMove();
            break;
        case PlayerType::AlphaBeta:
            potentialMove = getAlphaBetaMove();
            break; */
    }
    if (potentialMove) {
        _board.makeMove(*potentialMove, _currPlayer);
        changeTurn();
        _display.resetSelected();
        _display.setPrevMove(*potentialMove);
    }
}

bool CheckersGame::isOver() const {
    return !_display.isOpen();
}

std::optional<Move> CheckersGame::getMoveIfLegal(
        Board::Tile prevSelected, Board::Tile currSelected) const {
    Move move{prevSelected, currSelected};
    auto legalMoves = generateMoves(_board, _currPlayer);
    auto it = std::find_if(legalMoves.begin(), legalMoves.end(),
                           [move](const Move &legalMove) {
                               return ( legalMove.getStart() == move.getStart() &&
                                        legalMove.getEnd()   == move.getEnd() ) ||
                                      ( legalMove.tiles[0] == move.getStart() &&
                                        legalMove.tiles[1] == move.getEnd() );
                           });
    if (it == legalMoves.end()) {
        return {};
    }
    return *it;
}

void CheckersGame::changeTurn() {
    _currPlayer = 1 - _currPlayer;
}

void CheckersGame::displayBoard() {
    _display.drawBoard(_board, 0, _currPlayer);
}

void CheckersGame::handleInputs() {
    _display.handleInputs(_board, 0);
}

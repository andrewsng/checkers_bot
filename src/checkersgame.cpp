#include "checkersgame.hpp"
#include "move.hpp"
#include "movegen.hpp"
#include "searching.hpp"
#include <optional>
using std::optional;
#include <random>


CheckersGame::CheckersGame(Board board, int currPlayer)
    :_board(board), _currPlayer(currPlayer)
{}

void CheckersGame::setRedPlayer(PlayerType type) {
    _redPlayerType = type;
}

void CheckersGame::setBlackPlayer(PlayerType type) {
    _blackPlayerType = type;
}

void CheckersGame::createDisplay() {
    _display = std::make_unique<CheckersDisplay>(1000, 1000, "Checkers");
}

void CheckersGame::runGame() {
    displayBoard();
    while (!isGameOver()) {
        handleInputs();
        if (_display && !isDisplayOpen()) {
            break;
        }
        attemptMove();
        displayBoard();
    }
    result();
    while (_display && isDisplayOpen()) {
        handleInputs();
        displayBoard();
    }
}

void CheckersGame::attemptMove() {
    auto currPlayerType = (_currPlayer == 0) ? _redPlayerType
                                             : _blackPlayerType;
    optional<Move> potentialMove{};
    switch (currPlayerType) {
        case PlayerType::Human:
            potentialMove = getMoveIfLegal(_display->getPrevSelected(),
                                           _display->getCurrSelected());
            break;
        case PlayerType::Random:
            potentialMove = getRandomMove();
            break;
        case PlayerType::MiniMax:
            potentialMove = miniMax(_board, _currPlayer, 7);
            break;
        case PlayerType::AlphaBeta:
            potentialMove = alphaBeta(_board, _currPlayer, 10);
            break;
        case PlayerType::MCTS:
            potentialMove = monteCarlo(_board, _currPlayer, 100000);
            break;
    }
    if (potentialMove) {
        _board.makeMove(*potentialMove, _currPlayer);
        _moveHistory.push_back({*potentialMove, _currPlayer});
        changeTurn();
        resetDisplay(*potentialMove);
    }
}

GameResult CheckersGame::result() const {
    GameResult result{};
    if (_moveHistory.size() > 1000) {
        result = GameResult::Draw;
    } else if (generateMoves(_board, _currPlayer).empty()) {
        result = (_currPlayer == 1) ? GameResult::RedWin
                                    : GameResult::BlackWin;
    }
    return result;
}

bool CheckersGame::isGameOver() const {
    auto legalMoves = generateMoves(_board, _currPlayer);
    return legalMoves.empty() || (_moveHistory.size() > 1000);
}

bool CheckersGame::isDisplayOpen() const {
    if (_display) {
        return _display->isOpen();
    }
    return false;
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

std::optional<Move> CheckersGame::getRandomMove() const {
    static std::random_device rd{};
    static std::mt19937 gen(rd());
    auto legalMoves = generateMoves(_board, _currPlayer);
    if (legalMoves.empty()) {
        return {};
    }
    std::uniform_int_distribution<std::size_t> dist(0ull, legalMoves.size() - 1);
    return legalMoves[dist(gen)];
}

void CheckersGame::changeTurn() {
    _currPlayer = 1 - _currPlayer;
}

void CheckersGame::displayBoard() {
    if (_display) {
        _display->drawBoard(_board, 0, _currPlayer);
    }
}

void CheckersGame::handleInputs() {
    if (_display) {
        _display->handleInputs(_board, 0);
    }
}

void CheckersGame::resetDisplay(const Move &prevMove) {
    if (_display) {
        _display->resetSelected();
        _display->setPrevMove(prevMove);
    }
}

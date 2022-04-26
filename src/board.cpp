#include "board.hpp"
#include "move.hpp"
#include "movegen.hpp"
#include "searching.hpp"
#include <vector>
using std::vector;
#include <optional>
using std::optional;
#include <cctype>
using std::toupper;

vector<Board::Tile> Board::getRedPositions() const {
    vector<Tile> redPositions{};
    for (Tile i = 0; i < _numTiles; ++i) {
        if (_data[i] == 'r' || _data[i] == 'R') {
            redPositions.push_back(i);
        }
    }
    return redPositions;
}

vector<Board::Tile> Board::getBlackPositions() const {
    vector<Tile> blackPositions{};
    for (Tile i = 0; i < _numTiles; ++i) {
        if (_data[i] == 'b' || _data[i] == 'B') {
            blackPositions.push_back(i);
        }
    }
    return blackPositions;
}

vector<float> Board::getEncoding(float kingValue) const {
    vector<float> encoding(32, 0.0f);
    for (Tile i = 0; i < _numTiles; ++i) {
        float val = 0.0f;
        if (isRed(i)) {
            val = 1.0f;
        }
        else {
            val = -1.0f;
        }
        if (isKing(i)) {
            val *= kingValue;
        }
        encoding[i] = val;
    }
    return encoding;
}

optional<Move> Board::getBotMove(int player) const {
    return miniMax(*this, player, 8);
}

bool Board::onEvenRow(Tile tile) {
    return (tile / 4) % 2 == 0;
}

bool Board::onLeftSide(Tile tile) {
    return tile % 8 == 0;
}

bool Board::onRightSide(Tile tile) {
    return tile % 8 == 7;
}

bool Board::isRed(Tile tile) const {
    return _data[tile] == 'r' || _data[tile] == 'R';
}

bool Board::isBlack(Tile tile) const {
    return _data[tile] == 'b' || _data[tile] == 'B';
}

bool Board::isKing(Tile tile) const {
    return _data[tile] == 'R' || _data[tile] == 'B';
}

bool Board::isOccupied(Tile tile) const {
    return _data[tile] != ' ';
}

bool Board::isOutOfBounds(Tile tile) const {
    return tile >= _numTiles;
}

bool Board::isOpponent(Tile tile, int player) const {
    if (player == 0 && (_data[tile] == 'b' || _data[tile] == 'B'))
        return true;
    if (player == 1 && (_data[tile] == 'r' || _data[tile] == 'R'))
        return true;
    return false;
}

bool Board::isPromotionRow(Tile tile, int player) const {
    if (player == 0) {
        return (0 <= tile) && (tile <= 3);
    }
    if (player == 1) {
        return (28 <= tile) && (tile <= 31);
    }
    return false;
}

bool Board::isPromotion(const Move &move, int player) const {
    return !isKing(move.getStart()) && isPromotionRow(move.getEnd(), player);
}

char Board::symbolOn(Tile tile) const {
    return _data[tile];
}

void Board::makeMove(const Move &move, int player) {
    auto &start = _data[move.getStart()];
    auto &end = _data[move.getEnd()];
    auto temp = start;
    start = ' ';
    end = temp;
    for (const auto &captured : move.getCaptured()) {
        _data[captured] = ' ';
    }
    if (isPromotion(move, player)) {
        end = toupper(end);
    }
}

double evalBoard(const Board &board, int player) {
    auto playerPieces   = (player == 0) ? board.getRedPositions() : board.getBlackPositions();
    auto opponentPieces = (player == 1) ? board.getRedPositions() : board.getBlackPositions();
    double checkerValue = 1.0;
    double kingValue = 1.5;
    double score{0.0};
    for (const auto &piece : playerPieces) {
        if (board.isKing(piece)) {
            score += kingValue;
        } else {
            score += checkerValue;
        }
    }
    for (const auto &piece : opponentPieces) {
        if (board.isKing(piece)) {
            score -= kingValue;
        } else {
            score -= checkerValue;
        }
    }
    return score;
}

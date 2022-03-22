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

int Board::getPlayer() const {
    return _player;
}

vector<Board::Tile> Board::getRedPositions() const {
    vector<Tile> redPositions{};
    for (Tile i = 0; i < _data.size(); ++i) {
        if (_data[i] == 'r' || _data[i] == 'R') {
            redPositions.push_back(i);
        }
    }
    return redPositions;
}

vector<Board::Tile> Board::getBlackPositions() const {
    vector<Tile> blackPositions{};
    for (Tile i = 0; i < _data.size(); ++i) {
        if (_data[i] == 'b' || _data[i] == 'B') {
            blackPositions.push_back(i);
        }
    }
    return blackPositions;
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
    return tile >= _data.size();
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

optional<Move> Board::getMoveIfLegal(const Move &move, int player) const {
    auto legalMoves = generateMoves(*this, player);
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

optional<Move> Board::getBotMove(int player) const {
    return miniMax(*this, player, 8);
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

void Board::changeTurn() {
    _player = 1 - getPlayer();
}

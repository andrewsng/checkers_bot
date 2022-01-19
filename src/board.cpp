#include "board.hpp"
using std::vector;

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

bool Board::onEvenRow(Tile tile) const {
    return (tile / 4) % 2 == 0;
}

bool Board::onLeftSide(Tile tile) const {
    return tile % 8 == 0;
}

bool Board::onRightSide(Tile tile) const {
    return tile % 8 == 7;
}

bool Board::isOccupied(Tile tile) const {
    return _data[tile] != ' ';
}

bool Board::isOpponent(Tile tile, int player) const {
    if (player == 0 && (_data[tile] == 'b' || _data[tile] == 'B'))
        return true;
    if (player == 1 && (_data[tile] == 'r' || _data[tile] == 'R'))
        return true;
    return false;
}

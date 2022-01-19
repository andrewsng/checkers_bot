#include "board.hpp"
using std::vector;


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
    return true;
}

bool Board::onLeftSide(Tile tile) const {
    return true;
}

bool Board::onRightSide(Tile tile) const {
    return true;
}

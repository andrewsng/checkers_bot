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
    return (tile / 4) % 2 == 0;
}

bool Board::onLeftSide(Tile tile) const {
    return tile % 8 == 0;
}

bool Board::onRightSide(Tile tile) const {
    return tile % 8 == 7;
}

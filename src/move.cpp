#include "move.hpp"
#include "board.hpp"
#include <vector>
using std::vector;
#include <cmath>


Move::Tile Move::getStart() const {
    return tiles.front();
}

Move::Tile Move::getEnd() const {
    return tiles.back();
}

Move::Move(std::initializer_list<Tile> tileList)
    :tiles(tileList)
{}

vector<Move::Tile> Move::getCaptured() const {
    vector<Move::Tile> capturedTiles{};
    if (!isAJump()) {
        return capturedTiles;
    }
    for (auto it = tiles.begin(); it != (tiles.end() - 1); ++it) {
        Tile start = *it;
        Tile end = *(it + 1);
        auto offset = Board::onEvenRow(start) ? 0ull : 1ull;
        auto closestToBot = std::min(start, end);
        if (tileDiff(start, end) == 7) {
            capturedTiles.push_back(closestToBot + offset + 3);
        }
        else {
            capturedTiles.push_back(closestToBot + offset + 4);
        }
    }
    return capturedTiles;
}

bool Move::isAJump() const {
    auto firstTwoDiff = tileDiff(tiles[0], tiles[1]);
    return (firstTwoDiff == 7) || (firstTwoDiff == 9);
}

Move::Diff Move::tileDiff(Move::Tile t0, Move::Tile t1) const {
    return std::max(t0, t1) - std::min(t0, t1);
}

bool operator==(const Move &lhs, const Move &rhs) {
    return lhs.tiles == rhs.tiles;
}

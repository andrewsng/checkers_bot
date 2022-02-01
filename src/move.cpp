#include "move.hpp"
#include <optional>
using std::optional;
#include <cmath>


Move::Move(Tile start, Tile end)
    :_start(start), _end(end)
{}

Move::Tile Move::getStart() const {
    return _start;
}

Move::Tile Move::getEnd() const {
    return _end;
}

optional<Move::Tile> Move::getCaptured() const {
    if (!isAJump()) {
        return {};
    }
    auto offset = Board::onEvenRow(getStart()) ? 0ull : 1ull;
    auto closestToBot = std::min(getStart(), getEnd());
    if (tileDiff() == 7) {
        return closestToBot + offset + 3;
    }
    else {
        return closestToBot + offset + 4;
    }
}

bool Move::isAJump() const {
    return (tileDiff() == 7) || (tileDiff() == 9);
}

Move::Diff Move::tileDiff() const {
    return std::max(getStart(), getEnd()) - std::min(getStart(), getEnd());
}

bool operator==(const Move &lhs, const Move &rhs) {
    return (lhs.getStart() == rhs.getStart() &&
            lhs.getEnd() == rhs.getEnd());
}

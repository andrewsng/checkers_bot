#include "movegen.hpp"
#include <optional>
using std::vector;
using std::optional;


// Forward declarations
void generateLeftRight(const Board &, int, vector<Move> &, Board::Tile, bool);
optional<Board::Tile> getLeft(const Board &, Board::Tile, bool);
optional<Board::Tile> getRight(const Board &, Board::Tile, bool);
void generateNextMove(const Board &, int, vector<Move> &, Board::Tile, bool,
                      decltype(getLeft) *);


vector<Move> generateMoves(const Board &board, int player) {
    vector<Move> moves{};
    bool isRed = (player == 0);
    auto positions = isRed ? board.getRedPositions() : board.getBlackPositions();
    for (const auto &tile : positions) {
        generateLeftRight(board, player, moves, tile, !isRed);
        if (board.isKing(tile)) {
            generateLeftRight(board, player, moves, tile, isRed);
        }
    }
    return moves;
}

void generateLeftRight(const Board &board, int player, vector<Move> &moves,
                       Board::Tile tile, bool isUpward) {
    generateNextMove(board, player, moves, tile, isUpward, getLeft);
    generateNextMove(board, player, moves, tile, isUpward, getRight);
}

void generateNextMove(const Board &board, int player, vector<Move> &moves,
                  Board::Tile tile, bool isUpward, decltype(getLeft) *getNext) {
    if (auto nextTile = getNext(board, tile, isUpward)) {
        if (!board.isOccupied(*nextTile)) {
            moves.push_back(Move{tile, *nextTile, player});
        } else if (auto nextJump = getNext(board, *nextTile, isUpward)) {
            if (board.isOpponent(*nextTile, player) && !board.isOccupied(*nextJump)) {
                moves.push_back(Move{tile, *nextJump, player});
            }
        }
    }
}

optional<Board::Tile> getLeft(const Board &board, Board::Tile tile, bool up) {
    Board::Tile ret{};
    if (board.onEvenRow(tile)) {
        if (board.onLeftSide(tile)) {
            return {};
        } else if (up) {
            ret = tile + 3;
        } else {
            ret = tile - 5;
        }
    } else if (up) {
        ret = tile + 4;
    } else {
        ret = tile - 4;
    }
    return board.isOutOfBounds(ret) ? optional<Board::Tile>{} : ret;
}

optional<Board::Tile> getRight(const Board &board, Board::Tile tile, bool up) {
    Board::Tile ret{};
    if (!board.onEvenRow(tile)) {
        if (board.onRightSide(tile)) {
            return {};
        } else if (up) {
            ret = tile + 5;
        } else {
            ret = tile - 3;
        }
    } else if (up) {
        ret = tile + 4;
    } else {
        ret = tile - 4;
    }
    return board.isOutOfBounds(ret) ? optional<Board::Tile>{} : ret;
}

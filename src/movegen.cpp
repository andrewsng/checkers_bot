#include "movegen.hpp"
#include <optional>
using std::vector;
using std::optional;


optional<Board::Tile> getLeft(const Board &board, Board::Tile tile, bool up) {
    if (board.onEvenRow(tile)) {
        if (!board.onLeftSide(tile)) {
            if (up) {
                return tile + 3;
            }
            return tile - 5;
        }
        return {};
    }
    else if (up) {
        return tile + 4;
    }
    return tile - 4;
}

optional<Board::Tile> getRight(const Board &board, Board::Tile tile, bool up) {
    if (!board.onEvenRow(tile)) {
        if (!board.onRightSide(tile)) {
            if (up) {
                return tile + 5;
            }
            return tile - 3;
        }
        return {};
    }
    else if (up) {
        return tile + 4;
    }
    return tile - 4;
}

void generateLeftRight(const Board &board, int player, vector<Move> &moves, Board::Tile tile, bool isUpward) {
    if (auto left = getLeft(board, tile, isUpward)) {
        if (!board.isOccupied(*left)) {
            moves.push_back({tile, *left});
        } else if (auto leftJump = getLeft(board, *left, isUpward)) {
            if (board.isOpponent(*left, player) && !board.isOccupied(*leftJump)) {
                moves.push_back({tile, *leftJump});
            }
        }
    }
    if (auto right = getRight(board, tile, isUpward)) {
        if (!board.isOccupied(*right)) {
            moves.push_back({tile, *right});
        } else if (auto rightJump = getRight(board, *right, isUpward)) {
            if (board.isOpponent(*right, player) && !board.isOccupied(*rightJump)) {
                moves.push_back({tile, *rightJump});
            }
        }
    }
}

void generateUpwardMoves(const Board &board, int player, vector<Move> &moves, Board::Tile tile) {
    generateLeftRight(board, player, moves, tile, true);
}

void generateDownwardMoves(const Board &board, int player, vector<Move> &moves, Board::Tile tile) {
    generateLeftRight(board, player, moves, tile, false);
}

vector<Move> generateMoves(const Board &board, int player) {
    vector<Move> moves{};
    if (player == 1) {
        auto blackPositions = board.getBlackPositions();
        for (const auto &tile : blackPositions) {
            generateUpwardMoves(board, player, moves, tile);
        }
    }
    else {
        auto redPositions = board.getRedPositions();
        for (const auto &tile : redPositions) {
            generateDownwardMoves(board, player, moves, tile);
        }
    }
    return moves;
}

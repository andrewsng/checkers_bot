#include "searching.hpp"
#include "movegen.hpp"
#include <utility>
using std::pair;
using std::make_pair;
#include <optional>
using std::optional;
#include <random>
#include <limits>


pair<double, optional<Move>> maxMove(const Board &board, int player, int depth);
pair<double, optional<Move>> minMove(const Board &board, int player, int depth);
double evalBoard(const Board &board, int player);


optional<Move> miniMax(const Board &board, int player, int depth) {
    auto [dummy, bestMove] = maxMove(board, player, depth);
    if (bestMove) {
        return *bestMove;
    }
    else {
        return {};
    }
}

pair<double, optional<Move>> maxMove(const Board &board, int player, int depth) {
    auto moves = generateMoves(board, player);
    if (depth == 0 || moves.empty()) {
        return make_pair(evalBoard(board, player), optional<Move>{});
    }
    auto maxVal = std::numeric_limits<double>::lowest();
    Move maxMove = moves.front();
    for (const auto &move : moves) {
        Board next = board;
        next.updateBoard(move, player);
        auto [nextVal, dummy] = minMove(next, 1 - player, depth - 1);
        if (nextVal > maxVal) {
            maxVal = nextVal;
            maxMove = move;
        }
    }
    return make_pair(maxVal, maxMove);
}

pair<double, optional<Move>> minMove(const Board &board, int player, int depth) {
    auto moves = generateMoves(board, player);
    if (depth == 0 || moves.empty()) {
        return make_pair(evalBoard(board, 1 - player), optional<Move>{});
    }
    auto minVal = std::numeric_limits<double>::max();
    Move minMove = moves.front();
    for (const auto &move : moves) {
        Board next = board;
        next.updateBoard(move, player);
        auto [nextVal, dummy] = maxMove(next, 1 - player, depth - 1);
        if (nextVal < minVal) {
            minVal = nextVal;
            minMove = move;
        }
    }
    return make_pair(minVal, minMove);
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

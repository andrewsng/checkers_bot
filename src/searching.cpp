#include "searching.hpp"
#include "movegen.hpp"
#include <iostream>
#include <iomanip>
#include <utility>
using std::pair;
using std::make_pair;
#include <optional>
using std::optional;
#include <random>
#include <limits>
#include <cmath>


pair<double, optional<Move>> maxMove(const Board &, int, int, int &);
pair<double, optional<Move>> minMove(const Board &, int, int, int &);
pair<double, optional<Move>> alphaBetaMax(const Board &, int, int, double, double, int &);
pair<double, optional<Move>> alphaBetaMin(const Board &, int, int, double, double, int &);
double evalBoard(const Board &, int);


optional<Move> miniMax(const Board &board, int player, int depth) {
    int count{0};
    auto [dummy, bestMove] = maxMove(board, player, depth, count);
    std::cout << "MiniMax Board Count: " << std::right << std::setw(12) << count << "\n";
    if (bestMove) {
        return *bestMove;
    }
    else {
        return {};
    }
}

pair<double, optional<Move>> maxMove(const Board &board, int player, int depth, int &count) {
    ++count;
    auto moves = generateMoves(board, player);
    if (depth == 0 || moves.empty()) {
        return make_pair(evalBoard(board, player), optional<Move>{});
    }
    auto maxVal = std::numeric_limits<double>::lowest();
    Move maxMove = moves.front();
    for (const auto &move : moves) {
        Board next = board;
        next.makeMove(move, player);
        auto [nextVal, dummy] = minMove(next, 1 - player, depth - 1, count);
        if (nextVal > maxVal) {
            maxVal = nextVal;
            maxMove = move;
        }
    }
    return make_pair(maxVal, maxMove);
}

pair<double, optional<Move>> minMove(const Board &board, int player, int depth, int &count) {
    ++count;
    auto moves = generateMoves(board, player);
    if (depth == 0 || moves.empty()) {
        return make_pair(evalBoard(board, 1 - player), optional<Move>{});
    }
    auto minVal = std::numeric_limits<double>::max();
    Move minMove = moves.front();
    for (const auto &move : moves) {
        Board next = board;
        next.makeMove(move, player);
        auto [nextVal, dummy] = maxMove(next, 1 - player, depth - 1, count);
        if (nextVal < minVal) {
            minVal = nextVal;
            minMove = move;
        }
    }
    return make_pair(minVal, minMove);
}

optional<Move> alphaBeta(const Board &board, int player, int depth) {
    int count{0};
    auto [dummy, bestMove] = alphaBetaMax(board, player, depth,
            std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), count);
    std::cout << "alphaBeta Board Count: " << std::right << std::setw(12) << count << "\n";
    if (bestMove) {
        return *bestMove;
    }
    else {
        return {};
    }
}

pair<double, optional<Move>> alphaBetaMax(const Board &board, int player, int depth,
        double alpha, double beta, int &count) {
    ++count;
    auto moves = generateMoves(board, player);
    if (depth == 0 || moves.empty()) {
        return make_pair(evalBoard(board, player), optional<Move>{});
    }
    auto maxVal = std::numeric_limits<double>::lowest();
    Move maxMove = moves.front();
    for (const auto &move : moves) {
        Board next = board;
        next.makeMove(move, player);
        auto [nextVal, dummy] = alphaBetaMin(next, 1 - player, depth - 1, alpha, beta, count);
        if (nextVal > maxVal) {
            maxVal = nextVal;
            maxMove = move;
        }
        if (maxVal >= beta) {
            return make_pair(maxVal, maxMove);
        }
        alpha = std::max(alpha, maxVal);
    }
    return make_pair(maxVal, maxMove);
}

pair<double, optional<Move>> alphaBetaMin(const Board &board, int player, int depth,
        double alpha, double beta, int &count) {
    ++count;
    auto moves = generateMoves(board, player);
    if (depth == 0 || moves.empty()) {
        return make_pair(evalBoard(board, 1 - player), optional<Move>{});
    }
    auto minVal = std::numeric_limits<double>::max();
    Move minMove = moves.front();
    for (const auto &move : moves) {
        Board next = board;
        next.makeMove(move, player);
        auto [nextVal, dummy] = alphaBetaMax(next, 1 - player, depth - 1, alpha, beta, count);
        if (nextVal < minVal) {
            minVal = nextVal;
            minMove = move;
        }
        if (minVal <= alpha) {
            return make_pair(minVal, minMove);
        }
        beta = std::min(beta, minVal);
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

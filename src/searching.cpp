#include "searching.hpp"
#include "movegen.hpp"
#include "mctsnode.hpp"
#include <iostream>
#include <iomanip>
#include <utility>
using std::pair;
using std::make_pair;
#include <optional>
using std::optional;
#include <random>
#include <limits>
#include <chrono>
#include <cmath>
#include <functional>
using std::function;


pair<double, optional<Move>> maxMove(const Board &, int, int, int &);
pair<double, optional<Move>> minMove(const Board &, int, int, int &);
pair<double, optional<Move>> alphaBetaMax(const Board &, int, int, double, double, int &, function<double(const Board &, int)>);
pair<double, optional<Move>> alphaBetaMin(const Board &, int, int, double, double, int &, function<double(const Board &, int)>);
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
    int nextDepth = moves.front().isAJump() ? depth : depth - 1;
    auto maxVal = std::numeric_limits<double>::lowest();
    Move maxMove{};
    for (auto &move : moves) {
        Board next = board;
        next.makeMove(move, player);
        auto nextVal = minMove(next, 1 - player, nextDepth, count).first;
        if (nextVal > maxVal) {
            maxVal = nextVal;
            maxMove = std::move(move);
        }
    }
    return make_pair(maxVal, std::move(maxMove));
}

pair<double, optional<Move>> minMove(const Board &board, int player, int depth, int &count) {
    ++count;
    auto moves = generateMoves(board, player);
    if (depth == 0 || moves.empty()) {
        return make_pair(evalBoard(board, 1 - player), optional<Move>{});
    }
    int nextDepth = moves.front().isAJump() ? depth : depth - 1;
    auto minVal = std::numeric_limits<double>::max();
    Move minMove{};
    for (auto &move : moves) {
        Board next = board;
        next.makeMove(move, player);
        auto nextVal = maxMove(next, 1 - player, nextDepth, count).first;
        if (nextVal < minVal) {
            minVal = nextVal;
            minMove = std::move(move);
        }
    }
    return make_pair(minVal, std::move(minMove));
}

optional<Move> alphaBetaIDS(const Board &board, int player, int maxDepth,
        double timeLimitInSec, function<double(const Board &, int)> eval) {
    int depth = 1;
    optional<Move> moveToReturn{};
    auto start = std::chrono::steady_clock::now();
    while (depth <= maxDepth) {
        moveToReturn = alphaBeta(board, player, depth, eval);
        ++depth;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedSec = end - start;
        if (elapsedSec.count() >= timeLimitInSec * 0.5) {
            break;
        }
    }
    return moveToReturn;
}

optional<Move> alphaBeta(const Board &board, int player, int depth,
        function<double(const Board &, int)> eval) {
    int count{0};
    auto [dummy, bestMove] = alphaBetaMax(board, player, depth,
            std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), count, eval);
    std::cout << "alphaBeta Board Count: " << std::right << std::setw(12) << count << "\n";
    if (bestMove) {
        return *bestMove;
    }
    else {
        return {};
    }
}

pair<double, optional<Move>> alphaBetaMax(const Board &board, int player, int depth,
        double alpha, double beta, int &count, function<double(const Board &, int)> eval) {
    ++count;
    auto moves = generateMoves(board, player);
    if (depth == 0 || moves.empty()) {
        return make_pair(eval(board, player), optional<Move>{});
    }
    int nextDepth = moves.front().isAJump() ? depth : depth - 1;
    auto maxVal = std::numeric_limits<double>::lowest();
    Move maxMove{};
    for (const auto &move : moves) {
        Board next = board;
        next.makeMove(move, player);
        auto [nextVal, dummy] = alphaBetaMin(next, 1 - player, nextDepth, alpha, beta, count, eval);
        if (nextVal > maxVal) {
            maxVal = nextVal;
            maxMove = std::move(move);
        }
        if (maxVal >= beta) {
            return make_pair(maxVal, std::move(maxMove));
        }
        alpha = std::max(alpha, maxVal);
    }
    return make_pair(maxVal, std::move(maxMove));
}

pair<double, optional<Move>> alphaBetaMin(const Board &board, int player, int depth,
        double alpha, double beta, int &count, function<double(const Board &, int)> eval) {
    ++count;
    auto moves = generateMoves(board, player);
    if (depth == 0 || moves.empty()) {
        return make_pair(eval(board, 1 - player), optional<Move>{});
    }
    int nextDepth = moves.front().isAJump() ? depth : depth - 1;
    auto minVal = std::numeric_limits<double>::max();
    Move minMove{};
    for (const auto &move : moves) {
        Board next = board;
        next.makeMove(move, player);
        auto [nextVal, dummy] = alphaBetaMax(next, 1 - player, nextDepth, alpha, beta, count, eval);
        if (nextVal < minVal) {
            minVal = nextVal;
            minMove = std::move(move);
        }
        if (minVal <= alpha) {
            return make_pair(minVal, std::move(minMove));
        }
        beta = std::min(beta, minVal);
    }
    return make_pair(minVal, std::move(minMove));
}

optional<Move> monteCarlo(const Board &board, int player, int maxIters, double timeLimitInSec) {
    MCTSNode treeRoot{board, player};
    int iters = 0;
    auto start = std::chrono::steady_clock::now();
    while (iters < maxIters) {
        auto [leafToExpand, isTrueLeaf] = treeRoot.selectLeaf();
        MCTSNode *childToSimulate = leafToExpand;
        if (!isTrueLeaf) {
            childToSimulate = leafToExpand->expandLeaf();
        }
        auto result = childToSimulate->rollout();
        childToSimulate->propagateResult(result);
        ++iters;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedSec = end - start;
        if (elapsedSec.count() >= timeLimitInSec) {
            break;
        }
    }
    auto count = treeRoot.countNodes();
    std::cout << "Monte Carlo Board Count: " << std::right << std::setw(12) << count << "\n";
    return treeRoot.moveWithMostRollouts();
}

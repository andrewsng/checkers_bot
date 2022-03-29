#ifndef SEARCHING_HPP
#define SEARCHING_HPP

#include "board.hpp"
#include "move.hpp"
#include <optional>


std::optional<Move> miniMax(const Board &board, int player, int depth);
std::optional<Move> alphaBeta(const Board &board, int player, int depth);
std::optional<Move> alphaBetaIDS(const Board &board, int player, int maxDepth, double timeLimitInSec);
std::optional<Move> monteCarlo(const Board &board, int player, int maxIters, double timeLimitInSec);


#endif  // SEARCHING_HPP

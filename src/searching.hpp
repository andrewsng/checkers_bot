#ifndef SEARCHING_HPP
#define SEARCHING_HPP

#include "board.hpp"
#include "move.hpp"
#include <optional>


std::optional<Move> miniMax(Board board, int player, int depth);


#endif  // SEARCHING_HPP

#ifndef MOVEGEN_HPP
#define MOVEGEN_HPP

#include "board.hpp"
#include "move.hpp"
#include <vector>


std::vector<Move> generateMoves(const Board &board, int player);


#endif  // MOVEGEN_HPP

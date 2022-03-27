#include "catch.hpp"

#include "board.hpp"
#include "movegen.hpp"
#include <vector>
using std::vector;
#include <algorithm>


void testMoveGen(const Board &board, const vector<Move> &correctRedMoves,
        const vector<Move> &correctBlackMoves) {
    auto redMoves = generateMoves(board, 0);
    CHECK_THAT(redMoves, Catch::Matchers::UnorderedEquals(correctRedMoves));
    auto blackMoves = generateMoves(board, 1);
    CHECK_THAT(blackMoves, Catch::Matchers::UnorderedEquals(correctBlackMoves));
}


TEST_CASE("Move Generation - Simple Moves") {
    Board b;
    vector<Move> red = {
        Move{ 20, 16 }, Move{ 20, 17 }, Move{ 21, 17 }, Move{ 21, 18 },
        Move{ 22, 18 }, Move{ 22, 19 }, Move{ 23, 19 }
    };
    vector<Move> black = {
        Move{  8, 12 }, Move{  9, 12 }, Move{  9, 13 },
        Move{ 10, 13 }, Move{ 10, 14 }, Move{ 11, 14 }, Move{ 11, 15 }
    };
    testMoveGen(b, red, black);
}

#include "checkersgame.hpp"
#include "movegen.hpp"
#include "searching.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[]) {
    CheckersGame game{};
    game.setRedPlayer(PlayerType::MCTS);
    game.setBlackPlayer(PlayerType::AlphaBeta);
    game.createDisplay();
    game.threeMoveStart();
    game.runGame();
    return 0;
}

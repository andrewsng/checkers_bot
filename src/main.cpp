#include "checkersgame.hpp"
#include "movegen.hpp"
#include "searching.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[]) {
    CheckersGame game{};
    game.setRedPlayer(PlayerType::Human);
    game.setBlackPlayer(PlayerType::MiniMax);
    game.runGame();
    return 0;
}

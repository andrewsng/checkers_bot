#include "checkersgame.hpp"


void CheckersGame::setRedPlayer(PlayerType type)
{}

void CheckersGame::setBlackPlayer(PlayerType type)
{}

void CheckersGame::runGame()
{
    displayBoard();
    while (!isOver) {
        makeMove();
        displayBoard();
    }
}

#include "checkersgame.hpp"
#include "movegen.hpp"
#include <iostream>
using std::optional;


void CheckersGame::printBoard() const {
    for (int y = 7; y >= 0; --y) {
        for (int x = 0; x < 8; ++x) {
            if (x % 2 == y % 2) {
                Board::Tile tile = (x + y * 8) / 2;
                std::cout << _board.symbolOn(tile);
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

void CheckersGame::printRedMoves() const {
    auto redMoves = generateMoves(_board, 0);
    for (auto move : redMoves) {
        std::cout << move.getStart() << " -> " << move.getEnd() << ", ";
    }
}

void CheckersGame::printBlackMoves() const {
    auto blackMoves = generateMoves(_board, 1);
    for (auto move : blackMoves) {
        std::cout << move.getStart() << " -> " << move.getEnd() << ", ";
    }
}

void CheckersGame::drawBoard(sf::RenderWindow *window) const {
    auto size = window->getSize();
    auto boardSize = std::min(size.x, size.y);

    window->clear(sf::Color::Black);
    sf::RectangleShape boardBG(sf::Vector2f(boardSize, boardSize));
    boardBG.setFillColor(sf::Color(240, 215, 180));
    window->draw(boardBG);
    for (int tile = 0; tile < 32; ++tile) {
        int x = tile % 4;
        int y = 7 - (tile / 4);
        float xOffset = 0.0f;
        float yOffset = 0.0f;
        if (y % 2 == 0) {
            xOffset = (x * boardSize / 4.0f) + (boardSize / 8.0f);
            yOffset = y * boardSize / 8.0f;
        }
        else {
            xOffset = x * boardSize / 4.0f;
            yOffset = y * boardSize / 8.0f;
        }
        sf::RectangleShape tileSquare(sf::Vector2f(boardSize / 8.0f, boardSize / 8.0f));
        if (tile == _active) {
            tileSquare.setFillColor(sf::Color(255, 0, 255));
        }
        else {
            tileSquare.setFillColor(sf::Color(140, 70, 45));
        }
        tileSquare.move(xOffset, yOffset);
        window->draw(tileSquare);
        if (_board.isOccupied(tile)) {
            sf::CircleShape checker(boardSize / 16.0f);
            if (_board.isRed(tile)) {
                checker.setFillColor(sf::Color(255, 0, 0));
            }
            else if (_board.isBlack(tile)) {
                checker.setFillColor(sf::Color(0, 0, 0));
            }
            checker.move(xOffset, yOffset);
            window->draw(checker);
        }
    }
    window->display();
}

void CheckersGame::setActiveTile(int tile) {
    _active = tile;
}

void CheckersGame::changeTurn() {
    _player = 1 - _player;
}

optional<bool> CheckersGame::makeMove(Move move) {
    auto legalMoves = generateMoves(_board, _player);
    if (std::find(legalMoves.begin(), legalMoves.end(), move) == legalMoves.end()) {
        return {};
    }
    _board.updateBoard(move);
    if (_board.isPromotion(move) || !move.isAJump()) {
        return false;
    }
    auto continuedJumps = generateMoves(_board, _player);
    if (std::find_if(continuedJumps.begin(), continuedJumps.end(),
            [](const Move &nextMove) { return nextMove.isAJump(); }) == continuedJumps.end()) {
        return false;
    }
    return true;
}

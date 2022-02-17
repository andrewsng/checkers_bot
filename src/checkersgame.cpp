#include "checkersgame.hpp"
#include "movegen.hpp"
#include "searching.hpp"
#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>
using std::vector;
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

std::pair<float, float> coordsFromTile(Board::Tile tile, int boardSize) {
    auto x = tile % 4;
    auto y = 7 - (tile / 4);
    float xOffset = 0.0f;
    float yOffset = 0.0f;
    if (y % 2 == 0) {
        return std::make_pair((x * boardSize / 4.0f) + (boardSize / 8.0f),
                               y * boardSize / 8.0f);
    }
    else {
        return std::make_pair(x * boardSize / 4.0f,
                              y * boardSize / 8.0f);
    }
}

void CheckersGame::drawBoard(sf::RenderWindow *window) const {
    auto size = window->getSize();
    auto boardSize = std::min(size.x, size.y);

    window->clear(sf::Color::Black);
    sf::RectangleShape boardBG(sf::Vector2f(static_cast<float>(boardSize), static_cast<float>(boardSize)));
    boardBG.setFillColor(sf::Color(240, 215, 180));
    window->draw(boardBG);
    for (int tile = 0; tile < 32; ++tile) {
        auto [xOffset, yOffset] = coordsFromTile(tile, boardSize);
        sf::RectangleShape tileSquare(sf::Vector2f(boardSize / 8.0f, boardSize / 8.0f));
        if (tile == _active) {
            tileSquare.setFillColor(sf::Color(255, 240, 150));
        }
        else {
            tileSquare.setFillColor(sf::Color(180, 123, 95));
        }
        tileSquare.move(xOffset, yOffset);
        window->draw(tileSquare);
        if (_board.isOccupied(tile)) {
            float checkerWidth = boardSize / 16.0f;
            float checkerOutlineThickness = checkerWidth / 4.0f;
            sf::CircleShape checker(checkerWidth - checkerOutlineThickness);
            checker.setOutlineThickness(checkerOutlineThickness);
            if (_board.isRed(tile)) {
                checker.setFillColor(sf::Color(150, 25, 30));
                checker.setOutlineColor(sf::Color(215, 15, 25));
            }
            else if (_board.isBlack(tile)) {
                checker.setFillColor(sf::Color(15, 15, 15));
                checker.setOutlineColor(sf::Color(40, 40, 40));
            }
            checker.move(xOffset + checkerOutlineThickness, yOffset + checkerOutlineThickness);
            window->draw(checker);
        }
        if (_board.isKing(tile)) {
            float kingWidth = boardSize / 16.0f;
            sf::CircleShape king(boardSize / 16.0f / 2, 5);
            king.setFillColor(sf::Color(235, 190, 25));
            king.move(xOffset + (kingWidth / 2.0f), yOffset + (kingWidth * (1.0f - 0.5258f)));
            window->draw(king);
        }
    }
    for (const auto &move : getLegalMoves()) {
        for (auto it = move.tiles.begin(); it != (move.tiles.end() - 1); ++it) {
            auto [startX, startY] = coordsFromTile(*it, boardSize);
            auto [endX, endY] = coordsFromTile(*(it + 1), boardSize);
            auto offset = boardSize / 16.0f;
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(startX + offset, startY + offset)),
                sf::Vertex(sf::Vector2f(endX + offset, endY + offset))
            };
            window->draw(line, 2, sf::Lines);
        }
    }

    window->display();
}

vector<Move> CheckersGame::getLegalMoves() const {
    return _legalMovesCached ? _legalMoves : generateMoves(_board, _player);
}

void CheckersGame::setActiveTile(Board::Tile tile) {
    _active = tile;
}

void CheckersGame::changeTurn() {
    _player = 1 - _player;
}

bool CheckersGame::makeMove(Move move) {
    if (!_legalMovesCached) {
        _legalMoves = generateMoves(_board, _player);
        _legalMovesCached = true;
    }
    auto it = std::find_if(_legalMoves.begin(), _legalMoves.end(),
            [move](const Move &legalMove) {
                return legalMove.getStart() == move.getStart() &&
                       legalMove.getEnd()   == move.getEnd();
            });
    if (it == _legalMoves.end()) {
        return false;
    }
    _board.updateBoard(*it, _player);
    _legalMovesCached = false;
    return true;
}

void CheckersGame::makeBotMove() {
    if (auto move = miniMax(_board, _player, 8)) {
        makeMove(*move);
        changeTurn();
    }
}

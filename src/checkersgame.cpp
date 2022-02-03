#include "checkersgame.hpp"
#include "movegen.hpp"
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
        if (_board.isKing(tile)) {
            float kingWidth = boardSize / 16.0f;
            sf::CircleShape king(boardSize / 16.0f / 2, 5);
            king.setFillColor(sf::Color(255, 255, 0));
            king.move(xOffset + (kingWidth / 2.0f), yOffset + (kingWidth * (1.0f - 0.5258f)));
            window->draw(king);
        }
    }
    for (const auto &move : getLegalMoves()) {
        auto [startX, startY] = coordsFromTile(move.getStart(), boardSize);
        auto [endX, endY] = coordsFromTile(move.getEnd(), boardSize);
        auto offset = boardSize / 16.0f;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(startX + offset, startY + offset)),
            sf::Vertex(sf::Vector2f(endX + offset, endY + offset))
        };
        window->draw(line, 2, sf::Lines);
    }

    window->display();
}

vector<Move> CheckersGame::getLegalMoves() const {
    return _legalMovesCached ? _legalMoves : generateMoves(_board, _player);
}

void CheckersGame::setActiveTile(int tile) {
    _active = tile;
}

void CheckersGame::changeTurn() {
    _player = 1 - _player;
}

optional<bool> CheckersGame::makeMove(Move move) {
    if (!_legalMovesCached) {
        _legalMoves = generateMoves(_board, _player);
        _legalMovesCached = true;
    }
    if (std::find(_legalMoves.begin(), _legalMoves.end(), move) == _legalMoves.end()) {
        return {};
    }
    _board.updateBoard(move);
    if (_board.isPromotion(move) || !move.isAJump()) {
        _legalMovesCached = false;
        return false;
    }
    _legalMoves = generateMoves(_board, _player);
    _legalMoves.erase(std::remove_if(_legalMoves.begin(), _legalMoves.end(),
        [move](const Move &nextMove) { return nextMove.getStart() != move.getEnd() || !nextMove.isAJump(); }), _legalMoves.end());
    if (_legalMoves.empty()) {
        _legalMovesCached = false;
        return false;
    }
    return true;
}

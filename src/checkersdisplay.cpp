#include "checkersdisplay.hpp"
#include "board.hpp"
#include "move.hpp"
#include "movegen.hpp"
#include <string>
using std::string;
#include <SFML/Graphics.hpp>


CheckersDisplay::CheckersDisplay(int width, int height, string title)
    :_window(sf::VideoMode(width, height), title)
{}

bool CheckersDisplay::isOpen() const {
    return _window.isOpen();
}

Board::Tile CheckersDisplay::getPrevSelected() const {
    return _prevActive;
}

Board::Tile CheckersDisplay::getCurrSelected() const {
    return _currActive;
}

void CheckersDisplay::handleInputs(Board &game, int playerSide) {
    auto size = _window.getSize();
    auto boardSize = std::min(size.x, size.y);

    sf::Event event{};
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0.0f, 0.0f,
                    static_cast<float>(event.size.width),
                    static_cast<float>(event.size.height));
            _window.setView(sf::View(visibleArea));
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i clickPos = sf::Mouse::getPosition(_window);
                clickPos.y = boardSize - 1 - clickPos.y;
                int x = clickPos.x / (boardSize / 8);
                int y = clickPos.y / (boardSize / 8);
                if (0 <= x && x <= 7 &&
                    0 <= y && y <= 7 &&
                    (y % 2) == (x % 2)) {
                    _prevActive = _currActive;
                    _currActive = (y * 8 + x) / 2;
                    if (playerSide == 0) {
                        _currActive = 31 - _currActive;
                    }
                }
            }
        }
    }
}

std::pair<float, float> coordsFromTile(Board::Tile tile, int player, int boardSize) {
    if (player == 0) {
        tile = 31 - tile;
    }
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

void CheckersDisplay::drawBoard(const Board &game, int playerSide, int currPlayer) {
    auto size = _window.getSize();
    auto boardSize = std::min(size.x, size.y);

    _window.clear(sf::Color::Black);
    sf::RectangleShape boardBG(sf::Vector2f(static_cast<float>(boardSize), static_cast<float>(boardSize)));
    boardBG.setFillColor(sf::Color(240, 215, 180));
    _window.draw(boardBG);
    for (int tile = 0; tile < 32; ++tile) {
        auto [xOffset, yOffset] = coordsFromTile(tile, playerSide, boardSize);
        sf::RectangleShape tileSquare(sf::Vector2f(boardSize / 8.0f, boardSize / 8.0f));
        if (tile == _currActive || tile == _prevMove.getStart() || tile == _prevMove.getEnd()) {
            tileSquare.setFillColor(sf::Color(255, 240, 150));
        }
        else {
            tileSquare.setFillColor(sf::Color(180, 123, 95));
        }
        tileSquare.move(xOffset, yOffset);
        _window.draw(tileSquare);
        if (game.isOccupied(tile)) {
            float checkerWidth = boardSize / 16.0f;
            float checkerOutlineThickness = checkerWidth / 4.0f;
            sf::CircleShape checker(checkerWidth - checkerOutlineThickness);
            checker.setOutlineThickness(checkerOutlineThickness);
            if (game.isRed(tile)) {
                checker.setFillColor(sf::Color(150, 25, 30));
                checker.setOutlineColor(sf::Color(215, 15, 25));
            }
            else if (game.isBlack(tile)) {
                checker.setFillColor(sf::Color(15, 15, 15));
                checker.setOutlineColor(sf::Color(40, 40, 40));
            }
            checker.move(xOffset + checkerOutlineThickness, yOffset + checkerOutlineThickness);
            _window.draw(checker);
        }
        if (game.isKing(tile)) {
            float kingWidth = boardSize / 16.0f;
            sf::CircleShape king(boardSize / 16.0f / 2, 5);
            king.setFillColor(sf::Color(235, 190, 25));
            king.move(xOffset + (kingWidth / 2.0f), yOffset + (kingWidth * (1.0f - 0.5258f)));
            _window.draw(king);
        }
    }
    for (const auto &move : generateMoves(game, currPlayer)) {
        for (auto it = move.tiles.begin(); it != (move.tiles.end() - 1); ++it) {
            auto [startX, startY] = coordsFromTile(*it, playerSide, boardSize);
            auto [endX, endY] = coordsFromTile(*(it + 1), playerSide, boardSize);
            auto offset = boardSize / 16.0f;
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(startX + offset, startY + offset)),
                sf::Vertex(sf::Vector2f(endX + offset, endY + offset))
            };
            _window.draw(line, 2, sf::Lines);
        }
    }

    _window.display();
}

void CheckersDisplay::resetSelected() {
    _prevActive = _currActive = 32;
}

void CheckersDisplay::setPrevMove(Move prevMove) {
    _prevMove = prevMove;
}

#include "checkersgame.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <SFML/Graphics.hpp>

void botMove(CheckersGame &game) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    auto legalMoves = game.getLegalMoves();
    if (legalMoves.empty()) {
        game.changeTurn();
        return;
    }
    std::uniform_int_distribution<std::size_t> dist(0ull, legalMoves.size() - 1);
    if (game.makeMove(legalMoves[dist(gen)])) {
        game.changeTurn();
    }
}

int main(int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Checkers");
    sf::View view = window.getDefaultView();
    CheckersGame game{};
    game.drawBoard(&window);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    if (dist(gen)) {
        // botMove(game);
    }
    auto t0 = 0ull;
    auto t1 = 0ull;
    while (window.isOpen()) {
        auto size = window.getSize();
        auto boardSize = std::min(size.x, size.y);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0.0f, 0.0f,
                        static_cast<float>(event.size.width),
                        static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i clickPos = sf::Mouse::getPosition(window);
                    clickPos.y = boardSize - 1 - clickPos.y;
                    int x = clickPos.x / (boardSize / 8);
                    int y = clickPos.y / (boardSize / 8);
                    if (0 <= x && x <= 7 &&
                        0 <= y && y <= 7 &&
                        (y % 2) == (x % 2)) {
                        t0 = t1;
                        t1 = (y * 8 + x) / 2;

                        if (game.makeMove(Move{t0, t1})) {
                            game.setActiveTile(-1);
                            game.changeTurn();
                            game.drawBoard(&window);
                            game.makeBotMove();
                        }
                        else {
                            game.setActiveTile(t1);
                        }
                    }
                }
            }
        }
        game.drawBoard(&window);
    }
    return 0;
}

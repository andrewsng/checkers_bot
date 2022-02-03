#include "checkersgame.hpp"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>


int main(int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Checkers");
    sf::View view = window.getDefaultView();
    CheckersGame game{};
    auto t0 = 0ull;
    auto t1 = 0ull;
    int activeTile = -1;
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
                    std::cerr << x << " " << y << "\n";
                    if (0 <= x && x <= 7 &&
                        0 <= y && y <= 7 &&
                        (y % 2) == (x % 2)) {
                        t0 = t1;
                        t1 = (y * 8 + x) / 2;

                        if (auto cont = game.makeMove(Move{t0, t1, game.getTurn()})) {
                            game.printBoard();
                            std::cout << "\n";
                            if (!(*cont)) {
                                game.changeTurn();
                            }
                        }
                        else {
                            activeTile = t1;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        sf::RectangleShape rectangle(sf::Vector2f(boardSize, boardSize));
        rectangle.setFillColor(sf::Color(240, 215, 180));
        window.draw(rectangle);
        for (int tile = 0; tile < 32; ++tile) {
            sf::RectangleShape r(sf::Vector2f(boardSize / 8.0f, boardSize / 8.0f));
            if (tile == activeTile) {
                r.setFillColor(sf::Color(255, 0, 255));
            }
            else {
                r.setFillColor(sf::Color(140, 70, 45));
            }
            int x = tile % 4;
            int y = 7 - (tile / 4);
            if (y % 2 == 0) {
                r.move((x * boardSize / 4.0f) + boardSize / 8.0f, y * boardSize / 8.0f);
            }
            else {
                r.move(x * boardSize / 4.0f, y * boardSize / 8.0f);
            }
            window.draw(r);
        }
        window.display();
    }
    return 0;
}

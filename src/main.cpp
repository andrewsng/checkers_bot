#include "checkersgame.hpp"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>


int main(int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Checkers");
    sf::View view = window.getDefaultView();
    CheckersGame game{};
    int t0 = 0;
    int t1 = 0;
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

                        if (auto cont = game.makeMove(Move(t0, t1, game.getTurn()))) {
                            game.printBoard();
                            std::cout << "\n";
                            game.setActiveTile(-1);
                            if (!(*cont)) {
                                game.changeTurn();
                            }
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

#include "checkersgame.hpp"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>


int main(int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Checkers");
    sf::View view = window.getDefaultView();
    while (window.isOpen()) {
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
        }
        window.clear(sf::Color::Black);

        auto size = window.getSize();
        auto boardSize = std::min(size.x, size.y);
        sf::RectangleShape rectangle(sf::Vector2f(boardSize, boardSize));
        rectangle.setFillColor(sf::Color(240, 215, 180));
        window.draw(rectangle);
        for (int tile = 0; tile < 32; ++tile) {
            sf::RectangleShape r(sf::Vector2f(boardSize / 8.0f, boardSize / 8.0f));
            r.setFillColor(sf::Color(140, 70, 45));
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
    /* CheckersGame game{};
    while (true) {
        while (true) {
            game.printBoard();
            game.printRedMoves();
            std::cout << "\n";
            game.printBlackMoves();
            std::cout << "\n";
            Move::Tile t0{};
            Move::Tile t1{};
            std::cin >> t0 >> t1;
            if (auto cont = game.makeMove(Move{t0, t1, game.getTurn()})) {
                if (*cont) {
                    continue;
                }
                game.changeTurn();
                break;
            }
            std::cout << "Illegal Move.\n";
        }
    } */
    return 0;
}

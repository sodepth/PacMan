// Main.cpp
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Headers/Parameters.h"
#include "Headers/Game.h"

int main()
{
    using namespace PacMan;
    // Сид для rand()
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Game game;

    // Окно
    sf::RenderWindow window(
        sf::VideoMode(game.parameters.SCREEN_WIDTH, game.parameters.SCREEN_HEIGHT),
        "PacMan"
    );
    window.setFramerateLimit(144);

    // Инициализация игры
    BeginPlay(game, window);

    // Главный цикл
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            InputEvent(game, event, window);
        }

        float dt = game.clock.restart().asSeconds();
        if (game.state == PacMan::STATE_PLAY)
            Tick(game, dt, window);

        window.clear();
        DrawGame(game, window);
        window.display();
    }

    DeinitializeGame(game);
    return 0;
}

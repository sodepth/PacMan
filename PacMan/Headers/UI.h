#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace PacMan
{
    struct Game;
    struct Parameters;

    bool InitUI(const std::string& fontPath);
    void DrawUI(sf::RenderWindow& window, Game& _game, int eatenApples, float playerSpeed, Parameters& _parameters);
    void GameOverUi(sf::RenderWindow& window, Game& _game, Parameters& _parameters);
    void WinUi(sf::RenderWindow& window, Parameters& _parameters);
    void MenuUi (sf::RenderWindow& wnd, Game& g, Parameters& p);  
}

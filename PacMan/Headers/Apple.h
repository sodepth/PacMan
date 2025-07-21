#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace PacMan
{
    struct Parameters;
    struct Game;
    class Apple
    {
    public:
        sf::Vector2f position;
        sf::Sprite sprite;
        bool isRainbow = false;
        float chance = 3.141592f;
        
        //Инициализация яблока
        void InitApple(Parameters& _parameters, Game& _game,std::vector<sf::Vector2f>& _usedPos, const sf::Texture& tex);
        //Респавн
        void Respawn(Game& _game, Parameters& _parameters, const std::vector<sf::Vector2f>& used);
    };
}


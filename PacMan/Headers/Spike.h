#pragma once
#include <SFML/Graphics.hpp>

namespace PacMan
{struct Parameters;
     
     class Spike
     {
     public:
         sf::Vector2f position;
         sf::Sprite sprite;
     
         //Инициализация шипов
         void InitSpike(Parameters& _parameters, std::vector<sf::Vector2f>& _usedPos, const sf::Texture& tex);
     };

    
}


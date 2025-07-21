#pragma once
#include <SFML/Graphics.hpp>

namespace PacMan
{
    struct Parameters;
    struct Game;
    class Apple;
    
    class Player
    {
    public:
        sf::Vector2f position;
        sf::Vector2i direction;
        sf::Sprite sprite;
        float speed;
        
        //Инициализация игрока
        void InitPlayer(Parameters& _parameters, std::vector<sf::Vector2f>& _usedPos,
                        const sf::Texture& tex);
        //Поедание яблока
        void EatApple(Game& _game,std::vector<sf::Vector2f>& _usedPos,std::vector<Apple>& _apples,int& _eatenApples, int i);
    };

}

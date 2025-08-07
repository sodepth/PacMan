#pragma once
#include <SFML/Graphics.hpp>

#include "Headers/Leaderboard.h"


namespace PacMan
{
    struct Parameters;
    struct Math
    {

        // Генерация рандом позиции
        static sf::Vector2f GetRandomPos(int screen_width, int screen_height);

        static void FlipSprite(sf::Sprite& sprite, bool flipX, bool flipY);
        
        // Проверка на оверлап
        static bool IsOverlap(
            const sf::Vector2f& first,
            const sf::Vector2f& second, float minDist);

        // Проверка на столкновение
        static bool IsColliding(
            const sf::Vector2f& aPos, float aHalfSize,
            const sf::Vector2f& bPos, float bHalfSize);
        
        // Ставит обдж на рандомную позицию если свободна
        static sf::Vector2f PlaceObject(const std::vector<sf::Vector2f>& existing,Parameters& _game);

        // Устанавливает размер спрайта
        static void SetSpriteSize(sf::Sprite& sprite, float width, float height);

        // Устанавливает спрайту центр
        static void SetSpriteOrigin(sf::Sprite& sprite);
        
        
        
    };
}

    
#include "Headers/Math.h"
#include "Headers/Parameters.h"
#include <cstdlib>
#include <algorithm>

namespace PacMan
{
    sf::Vector2f Math::GetRandomPos(int screen_width, int screen_height)
    {
        return {
            static_cast<float>(std::rand()) / RAND_MAX * screen_width,
            static_cast<float>(std::rand()) / RAND_MAX * screen_height
        };
    }
    
    sf::Vector2f Math::PlaceObject(const std::vector<sf::Vector2f>& existing, Parameters& _game)
    {
        sf::Vector2f pos;
        sf::Vector2f center{
            _game.SCREEN_WIDTH * 0.5f,
            _game.SCREEN_HEIGHT * 0.5f
        };
        
        const float m = _game.SPAWN_BORDER_MARGIN;
        const float minX = m;
        const float maxX = _game.SCREEN_WIDTH - m;
        const float minY = m;
        const float maxY = _game.SCREEN_HEIGHT - m;
    
        do {
            pos = {
                static_cast<float>(std::rand()) / RAND_MAX * (maxX - minX) + minX,
                static_cast<float>(std::rand()) / RAND_MAX * (maxY - minY) + minY
            };
        } while (
            std::any_of(existing.begin(), existing.end(),
                [&](const sf::Vector2f& other) {
                    return IsOverlap(pos, other, _game.SPAWN_MIN_DIST);
                })
            || IsOverlap(pos, center, _game.SPAWN_CENTER_RADIUS)
        );
    
        return pos;
    }
    
    bool Math::IsOverlap(const sf::Vector2f& first, const sf::Vector2f& second, float minDist)
    {
        float dx = first.x - second.x;
        float dy = first.y - second.y;
        return (dx*dx + dy*dy) < (minDist * minDist);
    }
    
    bool Math::IsColliding(const sf::Vector2f& aPos, float aHalfSize,
                            const sf::Vector2f& bPos, float bHalfSize)
    {
        float dx = aPos.x - bPos.x;
        float dy = aPos.y - bPos.y;
        float r = aHalfSize + bHalfSize;
        return (dx*dx + dy*dy) <= (r * r);
    }
    
    void Math::SetSpriteSize(sf::Sprite& sprite, float width, float height)
    {
        sf::FloatRect rect = sprite.getLocalBounds();
        sf::Vector2f scale = { width / rect.width, height / rect.height };
        sprite.setScale(scale);
    }

    void Math::FlipSprite(sf::Sprite& sprite, bool flipX, bool flipY)
    {
        auto scale = sprite.getScale();
        scale.x = std::abs(scale.x) * (flipX ? -1.f : 1.f);
        scale.y = std::abs(scale.y) * (flipY ? -1.f : 1.f);
        sprite.setScale(scale);
    }
    

    void Math::SetSpriteOrigin(sf::Sprite& sprite)
    {
        sprite.setOrigin(sprite.getTexture()->getSize().x/2.f, sprite.getTexture()->getSize().y/2.f);
    }

}


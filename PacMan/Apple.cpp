#include "Headers/Apple.h"
#include "Headers/Parameters.h"
#include "Headers/Math.h"
#include "Headers/Game.h"

namespace PacMan
{
    void Apple::InitApple(Parameters& _parameters, Game& _game,std::vector<sf::Vector2f>& _usedPos, const sf::Texture& tex)
    {
        if (_game.modeFlags & PacMan::MODE_ACCELERATION)
        {
            isRainbow = (std::rand() % 100) < this->chance/2;
        }
        this->sprite.setTexture(tex);
        Math::SetSpriteSize(this->sprite, _parameters.APPLE_SIZE, _parameters.APPLE_SIZE);
        Math::SetSpriteOrigin(this->sprite);
            
        this->position = Math::PlaceObject(_usedPos, _parameters);
        this->sprite.setPosition(this->position);
        _usedPos.push_back(this->position);
    }
    
    void Apple::Respawn(Game& _game, Parameters& _parameters, const std::vector<sf::Vector2f>& used)
    {
        if (_game.modeFlags & PacMan::MODE_ACCELERATION)
        {
            isRainbow = (std::rand() % 100) < this->chance/2;
        }
        position = Math::PlaceObject(used, _parameters);
        sprite.setPosition(position);
    }

}

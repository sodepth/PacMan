#include "Headers/player.h"
#include "Headers/Game.h"

namespace PacMan
{
    void Player::InitPlayer(Parameters& _parameters, std::vector<sf::Vector2f>& _usedPos,
                            const sf::Texture& tex)
    {
        this->position  = { static_cast<float>(_parameters.SCREEN_WIDTH)  / 2.f,
                                static_cast<float>(_parameters.SCREEN_HEIGHT) / 2.f };
        this->direction = { 0, 0 };
        this->speed = _parameters.INITIAL_SPEED;

        this->sprite.setTexture(tex);
        Math::SetSpriteSize(this->sprite, _parameters.PLAYER_SIZE, _parameters.PLAYER_SIZE);
        Math::SetSpriteOrigin(this->sprite);
        this->sprite.setPosition(this->position);
    
        _usedPos.push_back(this->position);
    }
    
    void Player::EatApple(Game& _game,std::vector<sf::Vector2f>& _usedPos,std::vector<Apple>& _apples,int& _eatenApples, int i)
    {
        ++_eatenApples;
        _game.sounds.PlayEatSound();
        
        if (_game.modeFlags & PacMan::MODE_ACCELERATION)
        {
            if (_apples[i].isRainbow)
                speed *= 0.5f;
            else
                speed += _game.parameters.ACCELERATION;
        }

        _usedPos.erase(std::remove(_usedPos.begin() + 1,_usedPos.end(),_apples[i].position),_usedPos.end());
        _usedPos[0] = this->sprite.getPosition();

        if (_game.modeFlags & PacMan::MODE_INFINITE_APPLES)
        {
            
            _apples[i].Respawn(_game, _game.parameters, _usedPos);
            _usedPos.push_back(_apples[i].position);
        }
        else
        {
            _apples[i] = _apples.back();
            _apples.pop_back();
            --_game.applesCount;
        }
    }
}


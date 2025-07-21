#include "Headers/Spike.h"
#include "Headers/Parameters.h"
#include "Headers/Math.h"

namespace PacMan
{
   void Spike::InitSpike(Parameters& _parameters, std::vector<sf::Vector2f>& _usedPos,
                           const sf::Texture& tex)
   {
       this->sprite.setTexture(tex);
       Math::SetSpriteSize(this->sprite, _parameters.SPIKE_SIZE, _parameters.SPIKE_SIZE);
       Math::SetSpriteOrigin(this->sprite);
       
       this->position = Math::PlaceObject(_usedPos, _parameters);
       this->sprite.setPosition(this->position);
       _usedPos.push_back(this->position);
   }
 
}

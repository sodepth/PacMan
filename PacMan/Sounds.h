#pragma once
#include <SFML/Audio.hpp>
#include "Headers/Parameters.h"

namespace PacMan {
    struct Sounds {
        sf::SoundBuffer eatBuffer;
        sf::SoundBuffer winBuffer;
        sf::SoundBuffer loseBuffer;

        sf::Sound eatSound;
        sf::Sound winSound;
        sf::Sound loseSound;

        void InitSounds(Parameters& _parameters);
        void PlayEatSound();
        void PlayWinSound();
        void PlayLoseSound();
    };
}
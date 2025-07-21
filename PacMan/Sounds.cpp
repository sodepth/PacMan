#include "Sounds.h"

namespace PacMan {
    void Sounds::InitSounds(Parameters& _parameters) {
        if (!eatBuffer.loadFromFile(_parameters.SoundsPath + "Eat.wav"))
            throw std::runtime_error("Failed to load Eat sound");
        eatSound.setBuffer(eatBuffer);

        if (!winBuffer.loadFromFile(_parameters.SoundsPath + "Win.wav"))
            throw std::runtime_error("Failed to load Win sound");
        winSound.setBuffer(winBuffer);

        if (!loseBuffer.loadFromFile(_parameters.SoundsPath + "Lose.wav"))
            throw std::runtime_error("Failed to load Lose sound");
        loseSound.setBuffer(loseBuffer);
    }

    void Sounds::PlayEatSound() { eatSound.play(); }
    void Sounds::PlayWinSound() { winSound.play(); }
    void Sounds::PlayLoseSound() { loseSound.play(); }
}
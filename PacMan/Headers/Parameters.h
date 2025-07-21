#pragma once
#include "Headers/Player.h"
#include "Headers/Apple.h"
#include "Headers/Spike.h"

namespace PacMan
{
    struct Parameters
    {
        int applesForWin = 0;

        // Константы
        const int SCREEN_WIDTH = 960;
        const int SCREEN_HEIGHT = 720;
        const float INITIAL_SPEED = 100.f;
        const float ACCELERATION = 20.f;
        const float PLAYER_SIZE = 50.f;
        const float APPLE_SIZE = 45.f;
        const float SPIKE_SIZE = 55.f;
        const float SPAWN_MIN_DIST = 50;
        const float RESTART_DELAY = 2.f;
        const float  SPAWN_CENTER_RADIUS = 100.f;
        const float SPAWN_BORDER_MARGIN = 50.f;
        static const int SPIKES_COUNT = 10;
        const std::string ResPath = "Resources/";
        const std::string FontsPath = ResPath+"Fonts/";
        const std::string ImagePath = ResPath+"Images/";
        const std::string ShadersPath = ResPath+"Shaders/";
        const std::string SoundsPath = ResPath+"Sounds/";
    };
}

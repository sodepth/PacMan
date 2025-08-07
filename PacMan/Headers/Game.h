#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Parameters.h"
#include "Math.h"
#include "UI.h"
#include "Player.h"
#include "Apple.h"
#include "Spike.h"
#include "Sounds.h"
#include "Headers/Leaderboard.h"

namespace PacMan
{
    enum GameMode : uint8_t
    {
        MODE_ACCELERATION = 1 << 0, // Ускорение
        MODE_INFINITE_APPLES = 1 << 1, // Бесконечный режим
    };

    enum GameState
    {
        STATE_MENU,
        STATE_PLAY
    };
    
    struct Game {
        // Константы
        Parameters parameters;
        // Таблица рекордов
        std::vector<Record> playersScoreData;
        // Звуки
        Sounds sounds;
        
        // Ресурсы
        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture spikeTexture;
    
        // Игровые объекты
        Player player;
        std::vector<Apple> apples;
        Spike spikes[Parameters::SPIKES_COUNT];
    
        // Шейдеры
        sf::RenderTexture sceneTexture;
        sf::RectangleShape background;
        sf::Shader appleRainbowShader;
        sf::Shader backgroundShader;
        sf::Shader gameOverBlurShader;
        bool isBackgroundShaderLoaded;
        bool isBlurShaderLoaded;
        
        // Состояние игры
        int applesEatenCount;
        bool isGameFinished;
        bool isGameWin;
        float timeSinceGameFinish;
        int applesCount = 0;
        GameState state = STATE_MENU;
        uint8_t   modeFlags = 0; // Флаги игры
        
        // Для шейдеров
        sf::View view;
        sf::Clock shaderClock;
        float zoomLevel = 0.9f;
        float parallax = 0.05f;
        sf::Vector2f worldCenter;
    
        // Таймеры
        sf::Clock clock;
        sf::Time frameTimeAccumulator;
    
        // Занятые позиции для спавна
        std::vector<sf::Vector2f> occupiedPositions;
    };
    
    // Обновление ввода
    void InputEvent(Game& game, const sf::Event& event, sf::RenderWindow& window);
    
    // Инициализация
    void BeginPlay(Game& game, sf::RenderWindow& window);
    
    // Перезапуск игры
    void RestartGame(Game& game, sf::RenderWindow& window);
    
    // Апдейт логики
    void Tick(Game& game, float deltaTime, sf::RenderWindow& window);
    
    // Отрисовка
    void DrawGame(Game& game, sf::RenderWindow& window);
    
    // Выход из игры
    void DeinitializeGame(Game& game);

}

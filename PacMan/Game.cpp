#include "Headers/Game.h"
#include <iostream>

namespace PacMan
{
    void InputEvent(Game& game, const sf::Event& event, sf::RenderWindow& window)
    {
        if (event.type != sf::Event::KeyPressed) return;

        if (game.state == STATE_MENU)
        {
            if (event.key.code == sf::Keyboard::Num1)
                game.modeFlags ^= PacMan::MODE_ACCELERATION;
            else if (event.key.code == sf::Keyboard::Num2)
                game.modeFlags ^= PacMan::MODE_INFINITE_APPLES;
            else if (event.key.code == sf::Keyboard::Enter)
            {
                game.state = STATE_PLAY;
                BeginPlay(game, window);
            }
            return;
        }

        switch (event.key.code) {
        case sf::Keyboard::W: game.player.direction = {0, -1}; break;
        case sf::Keyboard::S: game.player.direction = {0, 1};  break;
        case sf::Keyboard::A: game.player.direction = {-1, 0}; break;
        case sf::Keyboard::D: game.player.direction = {1, 0};  break;
        default: break;
        }

        if (event.key.code == sf::Keyboard::R)
            RestartGame(game, window);

        if (event.key.code == sf::Keyboard::Escape && game.isGameFinished)
        {
            game.state         = STATE_MENU;
            game.isGameFinished= false;
            game.isGameWin     = false;
        }
    }


    void BeginPlay(Game& game, sf::RenderWindow& window) {
    // Загрузка текстур
    if (!game.playerTexture.loadFromFile(game.parameters.ImagePath + "player.png") ||
        !game.appleTexture.loadFromFile(game.parameters.ImagePath + "apple.png") ||
        !game.spikeTexture.loadFromFile(game.parameters.ImagePath + "spike.png")) {
        std::cerr << "error текстуры\n";
        window.close();
        return;
    }
    // Инициализация звуков
    game.sounds.InitSounds(game.parameters);

    // Настройка фона
    game.background.setSize({
        static_cast<float>(game.parameters.SCREEN_WIDTH),
        static_cast<float>(game.parameters.SCREEN_HEIGHT)
    });
    game.background.setPosition(0.f, 0.f);

    // Загрузка шейдеров
    if (!game.appleRainbowShader.loadFromFile(game.parameters.ShadersPath + "rainbow.frag", sf::Shader::Fragment))
        std::cerr << "error шейдер яблока\n";
    else
        game.appleRainbowShader.setUniform("time", 0.f);

    game.isBackgroundShaderLoaded = game.backgroundShader.loadFromFile(
        game.parameters.ShadersPath + "background.frag",
        sf::Shader::Fragment
    );
    if (!game.isBackgroundShaderLoaded)
        std::cerr << "error шейдер фона\n";
    else
        game.backgroundShader.setUniform("resolution", sf::Vector2f(window.getSize()));

    if (!game.sceneTexture.create(
        game.parameters.SCREEN_WIDTH,
        game.parameters.SCREEN_HEIGHT))
    {
        std::cerr << "error текстура экрана\n";
    }
    if (!game.gameOverBlurShader.loadFromFile(
        game.parameters.ShadersPath + "blur.frag",
        sf::Shader::Fragment))
    {
        std::cerr << "error шейдер блюра\n";
    } else
    {
        game.isBlurShaderLoaded = true;
        game.gameOverBlurShader.setUniform("resolution", sf::Vector2f(window.getSize()));
        game.gameOverBlurShader.setUniform("radius", 8.f);
    }

    // Загрузка шрифта
    if (!InitUI(game.parameters.FontsPath + "minecraft.ttf")) {
        std::cerr << "error шрифт\n";
    }

    // Инициализация камеры
    game.view.setSize(
        game.parameters.SCREEN_WIDTH * game.zoomLevel,
        game.parameters.SCREEN_HEIGHT * game.zoomLevel
    );
    game.worldCenter = {
        game.parameters.SCREEN_WIDTH * 0.5f,
        game.parameters.SCREEN_HEIGHT * 0.5f
    };
    game.view.setCenter(game.worldCenter);
    game.shaderClock.restart();

    // Сброс состояний
    game.clock.restart();
    game.frameTimeAccumulator = sf::Time::Zero;
    game.applesEatenCount = 0;
    game.isGameFinished = false;
    game.isGameWin = false;
    game.occupiedPositions.clear();
    game.player.direction = {0, 0};

    // Количество яблок и условие победы
    game.applesCount = 10 + std::rand() % 50;
    game.parameters.applesForWin = game.applesCount;
    game.apples.resize(game.applesCount);

    // Спавн объектов
    game.player.InitPlayer(game.parameters, game.occupiedPositions, game.playerTexture);

    for (int i = 0; i < game.applesCount; ++i)
        game.apples[i].InitApple(game.parameters, game, game.occupiedPositions, game.appleTexture);

    for (int i = 0; i < game.parameters.SPIKES_COUNT; ++i)
        game.spikes[i].InitSpike(game.parameters, game.occupiedPositions, game.spikeTexture);

    game.player.sprite.setRotation(0.f);
}
    static void DrawGameMenu(Game& game, sf::RenderWindow& window)
    {
        window.setView(window.getDefaultView());
        game.background.setPosition(0.f, 0.f);
        if (!game.isBackgroundShaderLoaded)
        {
            window.clear(sf::Color::Black);
            return;
        }
        game.backgroundShader.setUniform("time", game.shaderClock.getElapsedTime().asSeconds());
        window.draw(game.background, &game.backgroundShader);

        sf::Texture snapTex;
        snapTex.create(window.getSize().x, window.getSize().y);
        snapTex.update(window);
        sf::Sprite menuBg(snapTex);

        game.gameOverBlurShader.setUniform("texture", sf::Shader::CurrentTexture);
        window.draw(menuBg, &game.gameOverBlurShader);
    }


    void RestartGame(Game& game, sf::RenderWindow& window) {
        BeginPlay(game, window);
    }

    void Tick(Game& game, float deltaTime, sf::RenderWindow& window) {
        if (!game.isGameFinished) {
            game.player.sprite.move(
                game.player.direction.x * game.player.speed * deltaTime,
                game.player.direction.y * game.player.speed * deltaTime
            );
            sf::Vector2i dir = game.player.direction;
            if (dir.x > 0) {
                game.player.sprite.setRotation(0.f);
                Math::FlipSprite(game.player.sprite, false, false);
            } else if (dir.x < 0) {
                game.player.sprite.setRotation(0.f);
                Math::FlipSprite(game.player.sprite, true, false);
            } else if (dir.y > 0) {
                game.player.sprite.setRotation(90.f);
                Math::FlipSprite(game.player.sprite, false, false);
            } else if (dir.y < 0) {
                game.player.sprite.setRotation(270.f);
                Math::FlipSprite(game.player.sprite, false, false);
            }
            auto playerBounds = game.player.sprite.getGlobalBounds();
            sf::Vector2f playerPosition = game.player.sprite.getPosition();
            float playerRadius = playerBounds.width / 2.f;
            for (int i = 0; i < game.applesCount; ++i) {
                auto& apple = game.apples[i];
                float appleRadius = apple.sprite.getGlobalBounds().width / 2.f;
                if (Math::IsColliding(playerPosition, playerRadius, apple.sprite.getPosition(), appleRadius)) {
                    game.player.EatApple(game, game.occupiedPositions, game.apples, game.applesEatenCount, i);
                }
            }
            for (int i = 0; i < game.parameters.SPIKES_COUNT; ++i) {
                auto& spike = game.spikes[i];
                float spikeRadius = spike.sprite.getGlobalBounds().width / 2.f;
                if (Math::IsColliding(playerPosition, playerRadius, spike.sprite.getPosition(), spikeRadius)) {
                    game.isGameFinished = true;
                    game.sounds.PlayLoseSound();
                    break;
                }
            }
            if (playerBounds.left < 0 ||
                playerBounds.left + playerBounds.width > game.parameters.SCREEN_WIDTH ||
                playerBounds.top < 0 ||
                playerBounds.top + playerBounds.height > game.parameters.SCREEN_HEIGHT) {
                game.isGameFinished = true;
                game.sounds.PlayLoseSound();
            }
            if (game.applesEatenCount >= game.parameters.applesForWin &&
                !(game.modeFlags & PacMan::MODE_INFINITE_APPLES)) {
                game.isGameFinished = true;
                game.isGameWin = true;
                game.sounds.PlayWinSound();
            }
        }
        float t = game.shaderClock.getElapsedTime().asSeconds();
        if (game.isBackgroundShaderLoaded)
            game.backgroundShader.setUniform("time", t);
        game.appleRainbowShader.setUniform("time", t);
        sf::Vector2f playerPos = game.player.sprite.getPosition();
        sf::Vector2f offset = (playerPos - game.worldCenter) * game.parallax;
        game.view.setCenter(game.worldCenter + offset);
        game.background.setPosition(game.view.getCenter() - game.worldCenter);
    }

    void DrawGame(Game& game, sf::RenderWindow& window) {
        if (game.state == STATE_MENU)
        {
            DrawGameMenu(game, window);
            MenuUi(window, game, game.parameters);
            return;
        }
        game.sceneTexture.clear(sf::Color::Transparent);
        game.sceneTexture.setView(game.view);
        game.sceneTexture.draw(game.background, game.isBackgroundShaderLoaded ? &game.backgroundShader : nullptr);
        game.sceneTexture.draw(game.player.sprite);
        for (int i = 0; i < game.applesCount; ++i)
            game.sceneTexture.draw(game.apples[i].sprite, game.apples[i].isRainbow ? &game.appleRainbowShader : nullptr);
        for (int i = 0; i < game.parameters.SPIKES_COUNT; ++i)
            game.sceneTexture.draw(game.spikes[i].sprite);
        game.sceneTexture.display();
        sf::Sprite sceneSprite(game.sceneTexture.getTexture());
        window.setView(window.getDefaultView());
        if (game.isGameFinished && game.isBlurShaderLoaded) {
            game.gameOverBlurShader.setUniform("texture", sf::Shader::CurrentTexture);
            window.draw(sceneSprite, &game.gameOverBlurShader);
        } else {
            window.draw(sceneSprite);
        }
        if (!game.isGameFinished) {
            DrawUI(window, game, game.applesEatenCount, game.player.speed, game.parameters);
        } else if (game.isGameWin) {
            WinUi(window, game.parameters);
        } else {
            GameOverUi(window, game, game.parameters);
        }
    }

    void DeinitializeGame(Game& _game) {
    }
}

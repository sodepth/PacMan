#include "Headers/UI.h"
#include "Headers/Game.h"
#include "Headers/Parameters.h"

namespace PacMan
{
    sf::Font gameFont;
    sf::Text appleHudText;
    sf::Text appleGameOverText;
    sf::Text speedText;
    sf::Text inputText;
    sf::Text gameOverText1;
    sf::Text gameOverText3;
    sf::Text hint;
    sf::Text winText;
    sf::Text line;
    sf::RectangleShape fade;
    sf::RectangleShape darken;

    bool InitUI(const std::string& fontPath) {
        if (!gameFont.loadFromFile(fontPath))
            return false;

        appleHudText.setFont(gameFont);
        appleHudText.setCharacterSize(24);
        appleHudText.setFillColor(sf::Color::White);

        appleGameOverText.setFont(gameFont);
        appleGameOverText.setCharacterSize(24);
        appleGameOverText.setFillColor(sf::Color::White);

        speedText.setFont(gameFont);
        speedText.setCharacterSize(24);
        speedText.setFillColor(sf::Color::White);

        inputText.setFont(gameFont);
        inputText.setCharacterSize(24);
        inputText.setFillColor(sf::Color::White);

        gameOverText1.setFont(gameFont);
        gameOverText1.setCharacterSize(50);
        gameOverText1.setFillColor(sf::Color::Red);

        gameOverText3.setFont(gameFont);
        gameOverText3.setCharacterSize(20);
        gameOverText3.setFillColor(sf::Color::White);

        winText.setFont(gameFont);
        winText.setCharacterSize(48);
        winText.setFillColor(sf::Color(112, 230, 255));

        hint.setFont(gameFont);
        hint.setCharacterSize(20);
        hint.setFillColor(sf::Color::White);

        line.setFont(gameFont);
        line.setCharacterSize(28);
        line.setFillColor(sf::Color::White);

        return true;
    }

    // Отрисовка UI
    void DrawUI(sf::RenderWindow& window, Game& _game, int eatenApples, float playerSpeed, Parameters& _parameters)
    {
        // HUD яблок
        appleHudText.setOrigin(0.f, 0.f);
        if (_game.modeFlags & PacMan::MODE_INFINITE_APPLES)
            appleHudText.setString("Apples: " + std::to_string(eatenApples));
        else
            appleHudText.setString("Apples: " + std::to_string(eatenApples) + "/" + std::to_string(_parameters.applesForWin));
        appleHudText.setPosition(10.f, 10.f);
        window.draw(appleHudText);

        // HUD скорость
        if (_game.modeFlags & PacMan::MODE_ACCELERATION) {
            speedText.setString("Speed: " + std::to_string(static_cast<int>(playerSpeed)));
            speedText.setPosition(10.f, 40.f);
            window.draw(speedText);
        }

        // HUD подсказка управления
        inputText.setString("Controls: WASD to move, R to restart :3");
        inputText.setPosition((float)_parameters.SCREEN_WIDTH / 3, 20.f);
        window.draw(inputText);
    }

    // UI Проигрыша
    void GameOverUi(sf::RenderWindow& window, Game& _game, Parameters& _parameters)
    {
        darken.setSize({(float)_parameters.SCREEN_WIDTH, (float)_parameters.SCREEN_HEIGHT});
        darken.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(darken);

        gameOverText1.setString("GAME OVER");
        gameOverText1.setOrigin(gameOverText1.getLocalBounds().width / 2, gameOverText1.getLocalBounds().height / 2);
        gameOverText1.setPosition(_parameters.SCREEN_WIDTH / 2.f, _parameters.SCREEN_HEIGHT / 3.f);
        window.draw(gameOverText1);

        gameOverText3.setString("R to restart, ESC to menu");
        gameOverText3.setOrigin(gameOverText3.getLocalBounds().width / 2, gameOverText3.getLocalBounds().height / 2);
        gameOverText3.setPosition(_parameters.SCREEN_WIDTH / 2.f, _parameters.SCREEN_HEIGHT / 2.f);
        window.draw(gameOverText3);

        // Яблоки на экране проигрыша
        appleGameOverText.setString(
            (_game.modeFlags & PacMan::MODE_INFINITE_APPLES)
                ? "Apples: " + std::to_string(_game.applesEatenCount)
                : "Apples: " + std::to_string(_game.applesEatenCount) + "/" + std::to_string(_parameters.applesForWin)
        );
        appleGameOverText.setOrigin(
            appleGameOverText.getLocalBounds().width / 2,
            appleGameOverText.getLocalBounds().height / 2
        );
        appleGameOverText.setPosition(_parameters.SCREEN_WIDTH / 2.f, _parameters.SCREEN_HEIGHT / 2.f + 40.f);
        window.draw(appleGameOverText);
    }

    // UI Победы
    void WinUi(sf::RenderWindow& window, Parameters& _parameters)
    {
        fade.setSize({(float)_parameters.SCREEN_WIDTH, (float)_parameters.SCREEN_HEIGHT});
        fade.setFillColor(sf::Color(0, 0, 0, 140));
        window.draw(fade);

        winText.setString("YOU WIN! :D");
        winText.setOrigin(winText.getLocalBounds().width / 2, winText.getLocalBounds().height / 2);
        winText.setPosition(_parameters.SCREEN_WIDTH / 2.f, _parameters.SCREEN_HEIGHT / 3.f);
        window.draw(winText);

        hint.setString("R to restart, ESC to menu");
        hint.setOrigin(hint.getLocalBounds().width / 2, hint.getLocalBounds().height / 2);
        hint.setPosition(_parameters.SCREEN_WIDTH / 2.f, _parameters.SCREEN_HEIGHT / 2.f);
        window.draw(hint);
    }

    // UI Меню
    void MenuUi(sf::RenderWindow& window, Game& _game, Parameters& _parameters)
    {
        darken.setSize({(float)_parameters.SCREEN_WIDTH, (float)_parameters.SCREEN_HEIGHT});
        darken.setFillColor(sf::Color(0, 0, 0, 140));
        window.draw(darken);

        gameOverText1.setString("PacMan");
        gameOverText1.setOrigin(gameOverText1.getLocalBounds().width / 2, gameOverText1.getLocalBounds().height / 2);
        gameOverText1.setPosition(_parameters.SCREEN_WIDTH / 2.f, _parameters.SCREEN_HEIGHT / 4.f);
        window.draw(gameOverText1);

        auto drawLine = [&](const std::string& text, float y)
        {
            line.setString(text);
            line.setOrigin(line.getLocalBounds().width / 2, line.getLocalBounds().height / 2);
            line.setPosition(_parameters.SCREEN_WIDTH / 2.f, y);
            window.draw(line);
        };

        drawLine(
            std::string("[1] Acceleration: ") +
            ((_game.modeFlags & MODE_ACCELERATION) ? "ON" : "OFF"),
            _parameters.SCREEN_HEIGHT / 2.f - 30.f
        );

        drawLine(
            std::string("[2] Infinite apples: ") +
            ((_game.modeFlags & MODE_INFINITE_APPLES) ? "ON" : "OFF"),
            _parameters.SCREEN_HEIGHT / 2.f + 10.f
        );

        hint.setString("Press Enter to play");
        hint.setOrigin(hint.getLocalBounds().width / 2, hint.getLocalBounds().height / 2);
        hint.setPosition(_parameters.SCREEN_WIDTH / 2.f, _parameters.SCREEN_HEIGHT * 0.75f);
        window.draw(hint);
    }
}

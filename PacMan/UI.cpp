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

    
    bool InitUI(const std::string& fontPath)
    {
        if (!gameFont.loadFromFile(fontPath))
            return false;

        auto initText = [](sf::Text& t, unsigned size, const sf::Color& color)
        {
            t.setFont(gameFont);
            t.setCharacterSize(size);
            t.setFillColor(color);
        };

        initText(appleHudText, 24, sf::Color::White);
        initText(appleGameOverText, 24, sf::Color::White);
        initText(speedText, 24, sf::Color::White);
        initText(inputText, 24, sf::Color::White);
        initText(gameOverText1, 50, sf::Color::Red);
        initText(gameOverText3, 20, sf::Color::White);
        initText(winText, 48, sf::Color(112, 230, 255));
        initText(hint, 20, sf::Color::White);
        initText(line, 28, sf::Color::White);

        return true;
    }
    
    void DrawUI(sf::RenderWindow& window, Game& _game, int eatenApples, float playerSpeed, Parameters& _parameters)
    {
        appleHudText.setOrigin(0.f, 0.f);
        if (_game.modeFlags & PacMan::MODE_INFINITE_APPLES)
            appleHudText.setString("Apples: " + std::to_string(eatenApples));
        else
            appleHudText.setString(
                "Apples: " + std::to_string(eatenApples) + "/" +
                std::to_string(_parameters.applesForWin));
        appleHudText.setPosition(10.f, 10.f);
        window.draw(appleHudText);

        if (_game.modeFlags & PacMan::MODE_ACCELERATION)
        {
            speedText.setString("Speed: " + std::to_string(static_cast<int>(playerSpeed)));
            speedText.setPosition(10.f, 40.f);
            window.draw(speedText);
        }
        
        inputText.setString("Controls: WASD to move, R to restart :3");
        inputText.setPosition(static_cast<float>(_parameters.SCREEN_WIDTH) / 3.f, 20.f);
        window.draw(inputText);
    }
    
    void DrawLeaderboard(sf::RenderWindow& window, const std::vector<Record>& _records,
                         Parameters& _param)
    {
        sf::Text txt;
        txt.setFont(gameFont);
        txt.setCharacterSize(24);
        txt.setFillColor(sf::Color::White);

        float startY = _param.SCREEN_HEIGHT * 0.5f;
        line.setFillColor(sf::Color::Yellow);
        line.setString("LEADERBOARD");
        line.setOrigin(line.getLocalBounds().width * .5f, line.getLocalBounds().height * .5f);
        line.setPosition(_param.SCREEN_WIDTH * .5f, startY - 30.f);
        window.draw(line);
        line.setFillColor(sf::Color::White);
        
        for (size_t i = 0; i < _records.size(); ++i)
        {
            std::string s = std::to_string(i + 1) + ". " + _records[i].name +": " +
                             std::to_string(_records[i].score);
            txt.setString(s);
            txt.setOrigin(0.f, 0.f);
            txt.setPosition(( _param.SCREEN_WIDTH - txt.getLocalBounds().width) * 0.5f,
                             startY + i * 30.f);
            window.draw(txt);
        }
        
        line.setString("------------------");
        line.setOrigin(line.getLocalBounds().width * .5f, line.getLocalBounds().height * .5f);
        line.setPosition(_param.SCREEN_WIDTH * .5f, startY + _records.size() * 30.f + 10.f);
        window.draw(line);
    }
    
    void GameOverUi(sf::RenderWindow& window, Game& _game, Parameters& _parameters)
    {
        for (auto& rec : _game.playersScoreData) {
            if (rec.name == "Player") {
                rec.score = std::max(rec.score, _game.applesEatenCount);
                break;
            }
        }
        SortDescending(_game.playersScoreData);
        
        darken.setSize({ static_cast<float>(_parameters.SCREEN_WIDTH),
                         static_cast<float>(_parameters.SCREEN_HEIGHT) });
        darken.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(darken);
        
        gameOverText1.setString("GAME OVER");
        gameOverText1.setOrigin(gameOverText1.getLocalBounds().width * .5f,
                                gameOverText1.getLocalBounds().height * .5f);
        gameOverText1.setPosition(_parameters.SCREEN_WIDTH * .5f,
                                  _parameters.SCREEN_HEIGHT * .3f);
        window.draw(gameOverText1);
        
        appleGameOverText.setString(
            (_game.modeFlags & PacMan::MODE_INFINITE_APPLES) ?
                "Apples: " + std::to_string(_game.applesEatenCount) :
                "Apples: " + std::to_string(_game.applesEatenCount) + "/" +
                              std::to_string(_parameters.applesForWin));
        appleGameOverText.setOrigin(appleGameOverText.getLocalBounds().width * .5f,
                                    appleGameOverText.getLocalBounds().height * .5f);
        appleGameOverText.setPosition(_parameters.SCREEN_WIDTH * .5f,
                                      _parameters.SCREEN_HEIGHT * .4f);
        window.draw(appleGameOverText);
        
        const bool showLeaderboard = _game.modeFlags & PacMan::MODE_INFINITE_APPLES;
        float hintY = _parameters.SCREEN_HEIGHT * 0.5f;

        if (showLeaderboard)
        {
            DrawLeaderboard(window, _game.playersScoreData, _parameters);
            hintY += static_cast<float>(_game.playersScoreData.size()) * 30.f + 50.f;
        }
        else
        {
            hintY += 40.f;
        }
        
        gameOverText3.setString("R to restart, ESC to menu");
        gameOverText3.setOrigin(gameOverText3.getLocalBounds().width * .5f,
                                gameOverText3.getLocalBounds().height * .5f);
        gameOverText3.setPosition(_parameters.SCREEN_WIDTH * .5f, hintY);
        window.draw(gameOverText3);
    }
    
    void WinUi(sf::RenderWindow& window, Game& _game, Parameters& _parameters)
    {
        fade.setSize({ static_cast<float>(_parameters.SCREEN_WIDTH),
                       static_cast<float>(_parameters.SCREEN_HEIGHT) });
        fade.setFillColor(sf::Color(0, 0, 0, 140));
        window.draw(fade);
        
        winText.setString("YOU WIN! :D");
        winText.setOrigin(winText.getLocalBounds().width * .5f,
                          winText.getLocalBounds().height * .5f);
        winText.setPosition(_parameters.SCREEN_WIDTH * .5f,
                            _parameters.SCREEN_HEIGHT / 3.f);
        window.draw(winText);
        
        const bool showLeaderboard = _game.modeFlags & PacMan::MODE_INFINITE_APPLES;
        float hintY = _parameters.SCREEN_HEIGHT * 0.4f; // base just below title

        if (showLeaderboard)
        {
            DrawLeaderboard(window, _game.playersScoreData, _parameters);
            hintY += static_cast<float>(_game.playersScoreData.size()) * 30.f + 50.f;
        }
        else
        {
            hintY += 40.f; // when leaderboard hidden
        }
        
        hint.setString("R to restart, ESC to menu");
        hint.setOrigin(hint.getLocalBounds().width * .5f,
                       hint.getLocalBounds().height * .5f);
        hint.setPosition(_parameters.SCREEN_WIDTH * .5f, hintY);
        window.draw(hint);
    }
    
    void MenuUi(sf::RenderWindow& window, Game& _game, Parameters& _parameters)
    {
        darken.setSize({ static_cast<float>(_parameters.SCREEN_WIDTH),
                         static_cast<float>(_parameters.SCREEN_HEIGHT) });
        darken.setFillColor(sf::Color(0, 0, 0, 140));
        window.draw(darken);

        gameOverText1.setString("PacMan");
        gameOverText1.setOrigin(gameOverText1.getLocalBounds().width * .5f,
                                gameOverText1.getLocalBounds().height * .5f);
        gameOverText1.setPosition(_parameters.SCREEN_WIDTH * .5f,
                                  _parameters.SCREEN_HEIGHT / 4.f);
        window.draw(gameOverText1);
        
        auto drawLine = [&](const std::string& text, float y)
        {
            line.setString(text);
            line.setOrigin(line.getLocalBounds().width * .5f,
                            line.getLocalBounds().height * .5f);
            line.setPosition(_parameters.SCREEN_WIDTH * .5f, y);
            window.draw(line);
        };

        drawLine(
            std::string("[1] Acceleration: ") +
            ((_game.modeFlags & MODE_ACCELERATION) ? "ON" : "OFF"),
            _parameters.SCREEN_HEIGHT * .5f - 30.f);

        drawLine(
            std::string("[2] Infinite apples: ") +
            ((_game.modeFlags & MODE_INFINITE_APPLES) ? "ON" : "OFF"),
            _parameters.SCREEN_HEIGHT * .5f + 10.f);

        hint.setString("Press Enter to play");
        hint.setOrigin(hint.getLocalBounds().width * .5f,
                       hint.getLocalBounds().height * .5f);
        hint.setPosition(_parameters.SCREEN_WIDTH * .5f,
                         _parameters.SCREEN_HEIGHT * 0.75f);
        window.draw(hint);
    }
}

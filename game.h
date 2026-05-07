#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include "menu.h"
#include "cursor.h"

namespace RatBoiGaming {

    enum class GameState { MAIN_MENU, LOADING, PLAYING };

    class Game {
    public:
        Game(const std::string& title, int width, int height);
        void run();

    private:
        void processEvents();
        void update();
        void render();
        void startNewGame();
        void updateLoading();
        void updatePlaying();
        void renderLoading();
        void renderPlaying();
        void keepPlayerInBounds();

        sf::RenderWindow m_window;
        sf::Font m_font;
        GameState m_state;
        std::unique_ptr<Menu> m_menu;
        Cursor m_cursor;
        sf::Music m_backgroundMusic;

        sf::Clock m_clock;
        sf::Clock m_loadingClock;
        sf::Texture m_gameBackgroundTexture;
        sf::Sprite m_gameBackgroundSprite;
        sf::RectangleShape m_worldFloor;
        sf::CircleShape m_player;
        sf::Text m_loadingText;
        sf::Text m_helpText;
        float m_playerSpeed;
        int m_windowWidth;
        int m_windowHeight;
    };

} // namespace RatBoiGaming

#endif // GAME_H

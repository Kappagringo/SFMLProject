#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "cursor.h"

namespace RatBoiGaming {

    class Game {
    public:
        Game(const std::string& title, int width, int height);
        void run();

    private:
        enum class GameState {
            MAIN_MENU,
            PLAYING
        };

        void processEvents();
        void update();
        void render();

        void handleMainMenuInput();
        void renderMainMenu();

        GameState m_state;

        sf::RenderWindow m_window;
        sf::Font m_font;

        sf::Text m_titleText;
        sf::Text m_startText;
        sf::Text m_exitText;

        Cursor m_cursor; // Cursor object
    };

} // namespace RatBoiGaming

#endif

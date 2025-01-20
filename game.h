#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "menu.h"
#include "cursor.h" // Ensure Cursor is included
#include <SFML/Audio.hpp>
namespace RatBoiGaming {

    enum class GameState { MAIN_MENU, PLAYING };

    class Game {
    public:
        Game(const std::string& title, int width, int height);
        void run();

    private:
        void processEvents();
        void update();
        void render();

        sf::RenderWindow m_window;
        sf::Font m_font;
        GameState m_state;
        std::unique_ptr<Menu> m_menu; // Menu object
        Cursor m_cursor; // custom cursor object
        sf::Music m_backgroundMusic; //Main Menu Background Music
    };

} // namespace RatBoiGaming

#endif // GAME_H


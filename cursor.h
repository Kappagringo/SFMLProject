#ifndef CURSOR_H
#define CURSOR_H

#include <SFML/Graphics.hpp>

namespace RatBoiGaming {

    class Cursor {
    public:
        Cursor();

        void update(const sf::RenderWindow& window); // Update the cursor position
        void render(sf::RenderWindow& window);      // Render the cursor
        sf::Vector2f getPosition() const;           // Get the cursor's position

    private:
        sf::CircleShape m_cursorShape; // Graphical representation of the cursor
    };

} // namespace RatBoiGaming

#endif

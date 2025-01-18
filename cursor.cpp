#include "cursor.h"

namespace RatBoiGaming {

    Cursor::Cursor() {
        m_cursorShape.setRadius(6.0f); // Small circle for the cursor
        m_cursorShape.setFillColor(sf::Color::Red);
        m_cursorShape.setOrigin(5.0f, 5.0f); // Center the circle
    }

    void Cursor::update(const sf::RenderWindow& window) {
        // Update the cursor's position to match the mouse position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        m_cursorShape.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

    void Cursor::render(sf::RenderWindow& window) {
        window.draw(m_cursorShape);
    }

    sf::Vector2f Cursor::getPosition() const {
        return m_cursorShape.getPosition();
    }

} // namespace RatBoiGaming

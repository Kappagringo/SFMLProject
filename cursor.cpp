#include "cursor.h"

namespace RatBoiGaming {

    Cursor::Cursor() {
        m_cursorShape.setRadius(5.0f);
        m_cursorShape.setFillColor(sf::Color::Black);
        m_cursorShape.setOrigin(5.0f, 5.0f); // Center the shape
    }

    void Cursor::update(const sf::RenderWindow& window) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        m_cursorShape.setPosition(static_cast<sf::Vector2f>(mousePosition));
    }

    void Cursor::render(sf::RenderWindow& window) {
        window.draw(m_cursorShape);
    }

    sf::Vector2f Cursor::getPosition() const {
        return m_cursorShape.getPosition();
    }

} // namespace RatBoiGaming


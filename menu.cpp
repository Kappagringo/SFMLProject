#include "menu.h"
#include <iostream>
#include <cstdlib>

namespace RatBoiGaming {

Menu::Menu(const sf::Font& font, float width, float height)
    : m_backgroundTexture(),
      m_backgroundSprite(m_backgroundTexture),
      m_menuItems(),
      m_menuLabels(),
      m_selectedIndex(-1),
      m_cursor(),
      m_titleText(m_titleFont),
      m_titleFont() {
    // Load the background texture.
    if (!m_backgroundTexture.loadFromFile("Assets/background.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
        std::exit(-1);
    }

    m_backgroundSprite.setTexture(m_backgroundTexture, true);
    m_backgroundSprite.setScale({
        width / static_cast<float>(m_backgroundTexture.getSize().x),
        height / static_cast<float>(m_backgroundTexture.getSize().y)
    });

    // Load the title font.
    if (!m_titleFont.openFromFile("Assets/GallaeciaForte.ttf")) {
        std::cerr << "Failed to load title font!" << std::endl;
        std::exit(-1);
    }

    // Configure the title text.
    m_titleText.setFont(m_titleFont);
    m_titleText.setString("Northern Shadows");
    m_titleText.setCharacterSize(100);
    m_titleText.setFillColor(sf::Color::Black);

    sf::FloatRect textBounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f
    });
    m_titleText.setPosition({width / 2.0f, height / 2.0f - 100.0f});

    m_menuLabels = {"New Game", "Load Save", "Options", "Exit"};

    float startY = height / 2.0f;
    float itemSpacing = 50.0f;

    for (size_t i = 0; i < m_menuLabels.size(); ++i) {
        sf::Text text(font, m_menuLabels[i], 30);
        text.setFillColor(sf::Color::White);
        text.setPosition({width / 2.0f - 100.0f, startY + static_cast<float>(i) * itemSpacing});
        m_menuItems.push_back(text);
    }
}

void Menu::update(const sf::RenderWindow& window) {
    sf::Vector2f mousePosition = m_cursor.getPosition();

    for (size_t i = 0; i < m_menuItems.size(); ++i) {
        if (m_menuItems[i].getGlobalBounds().contains(mousePosition)) {
            m_menuItems[i].setFillColor(sf::Color::Black);
            m_selectedIndex = static_cast<int>(i);
        } else {
            m_menuItems[i].setFillColor(sf::Color::White);
        }
    }

    m_cursor.update(window);
}

void Menu::handleEvent(const sf::RenderWindow& window, const sf::Event& event, int& selectedOption) {
    const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>();
    if (mousePressed != nullptr && mousePressed->button == sf::Mouse::Button::Left) {
        for (size_t i = 0; i < m_menuItems.size(); ++i) {
            if (m_menuItems[i].getGlobalBounds().contains(m_cursor.getPosition())) {
                selectedOption = static_cast<int>(i);
            }
        }
    }
}

void Menu::render(sf::RenderWindow& window) {
    window.draw(m_backgroundSprite);
    window.draw(m_titleText);

    for (const auto& item : m_menuItems) {
        window.draw(item);
    }

    m_cursor.render(window);
}

} // namespace RatBoiGaming

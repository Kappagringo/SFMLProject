#include "menu.h"
#include <iostream>

namespace RatBoiGaming {

Menu::Menu(const sf::Font& font, float width, float height)
    : m_selectedIndex(-1), m_cursor() {
    // Load the background texture
    if (!m_backgroundTexture.loadFromFile("Assets/background.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
        exit(-1);
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(
        width / m_backgroundTexture.getSize().x,
        height / m_backgroundTexture.getSize().y
    );

    // Load the title font
    if (!m_titleFont.loadFromFile("Assets/GallaeciaForte.ttf")) {
        std::cerr << "Failed to load title font!" << std::endl;
        exit(-1);
    }

    // Configure the title text
    // Configure the title text
    m_titleText.setFont(m_titleFont);
    m_titleText.setString("Northern Shadows");
    m_titleText.setCharacterSize(100); // Increase font size for a bold look
    m_titleText.setFillColor(sf::Color::Black);

    // Get the text bounds to calculate the correct origin
    sf::FloatRect textBounds = m_titleText.getLocalBounds();

    // Adjust the origin to the center of the text
    m_titleText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                          textBounds.top + textBounds.height / 2.0f);

    // Position the text in the middle of the screen horizontally, and slightly above the middle vertically
    m_titleText.setPosition(width / 2.0f, height / 2.0f - 100); // Adjust the `-100` value to move it up/down

    // Define menu labels
    m_menuLabels = {"New Game", "Load Save", "Options", "Exit"};

    // Create menu items from labels
    float startY = height / 2;
    float itemSpacing = 50.f;

    for (size_t i = 0; i < m_menuLabels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(m_menuLabels[i]);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setPosition(width / 2 - 100, startY + i * itemSpacing);
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
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        for (size_t i = 0; i < m_menuItems.size(); ++i) {
            if (m_menuItems[i].getGlobalBounds().contains(m_cursor.getPosition())) {
                selectedOption = static_cast<int>(i);
                return;
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


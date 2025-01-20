#include "menu.h"
#include <iostream>

namespace RatBoiGaming {

    Menu::Menu(const sf::Font& font, float width, float height)
        : m_selectedIndex(-1), m_cursor() {
        // Load the background texture
        std::cout << "Loading background from: " << "assets/winter 8/background.png" << std::endl;

        if (!m_backgroundTexture.loadFromFile("assets/winter 8/background.png")) {
            std::cerr << "Failed to load background image!" << std::endl;
            exit(-1);
        }

        // Set the texture to the sprite
        m_backgroundSprite.setTexture(m_backgroundTexture);
        m_backgroundSprite.setScale(
            width / m_backgroundTexture.getSize().x,
            height / m_backgroundTexture.getSize().y
        );

        // Define menu labels
        m_menuLabels = {"New Game", "Load Save", "Options", "Exit"};

        // Create menu items from labels
        float startY = height / 2; // Starting Y position for menu items
        float itemSpacing = 50.f; // Space between menu items

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
        // Get the cursor position
        sf::Vector2f mousePosition = m_cursor.getPosition();

        // Update selection based on hover
        for (size_t i = 0; i < m_menuItems.size(); ++i) {
            if (m_menuItems[i].getGlobalBounds().contains(mousePosition)) {
                m_menuItems[i].setFillColor(sf::Color::Red);
                m_selectedIndex = static_cast<int>(i);
            } else {
                m_menuItems[i].setFillColor(sf::Color::White);
            }
        }

        // Update cursor
        m_cursor.update(window);
    }

    void Menu::handleEvent(const sf::RenderWindow& window, const sf::Event& event, int& selectedOption) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            for (size_t i = 0; i < m_menuItems.size(); ++i) {
                if (m_menuItems[i].getGlobalBounds().contains(m_cursor.getPosition())) {
                    selectedOption = static_cast<int>(i); // Pass the selected menu option
                    return;
                }
            }
        }
    }


    void Menu::render(sf::RenderWindow& window) {
        // Draw the background first
        window.draw(m_backgroundSprite);

        // Draw all menu items
        for (const auto& item : m_menuItems) {
            window.draw(item);
        }

        // Draw the cursor
        m_cursor.render(window);
    }

    void Menu::updateSelection(const sf::Vector2f& mousePosition) {
        for (size_t i = 0; i < m_menuItems.size(); ++i) {
            if (m_menuItems[i].getGlobalBounds().contains(mousePosition)) {
             m_menuItems[i].setFillColor(sf::Color::Red);
            } else {
                m_menuItems[i].setFillColor(sf::Color::White);
        }
    }
}

} // namespace RatBoiGaming

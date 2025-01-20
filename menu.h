//
// Created by jdavis on 1/20/2025.
//
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "cursor.h" // Include the Cursor header

namespace RatBoiGaming {

    class Menu {
    public:
        Menu(const sf::Font& font, float width, float height);

        void handleEvent(const sf::RenderWindow& window, const sf::Event& event, int& selectedOption);
        void update(const sf::RenderWindow& window);
        void render(sf::RenderWindow& window);

    private:
        sf::Texture m_backgroundTexture; // Background image
        sf::Sprite m_backgroundSprite;   // Background sprite
        std::vector<sf::Text> m_menuItems; // Holds the text objects for the menu
        std::vector<std::string> m_menuLabels; // Labels for the menu items
        int m_selectedIndex;
        Cursor m_cursor; // Custom cursor


        void updateSelection(const sf::Vector2f& mousePosition);
    };

} // namespace RatBoiGaming

#endif // MENU_H

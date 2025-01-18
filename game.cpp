#include "game.h"
#include <iostream>

namespace RatBoiGaming {

    Game::Game(const std::string& title, int width, int height)
        : m_window(sf::VideoMode(width, height), title), m_state(GameState::MAIN_MENU) {
        // Hide the system cursor
        m_window.setMouseCursorVisible(false);

        if (!m_font.loadFromFile("nunito.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            exit(-1);
        }

        m_titleText.setFont(m_font);
        m_titleText.setString("Sanguine Homesteader");
        m_titleText.setCharacterSize(50);
        m_titleText.setFillColor(sf::Color::Red);
        m_titleText.setPosition(200, 100);

        m_startText.setFont(m_font);
        m_startText.setString("Start Game");
        m_startText.setCharacterSize(30);
        m_startText.setFillColor(sf::Color::White);
        m_startText.setPosition(200, 250);

        m_exitText.setFont(m_font);
        m_exitText.setString("Exit");
        m_exitText.setCharacterSize(30);
        m_exitText.setFillColor(sf::Color::White);
        m_exitText.setPosition(200, 300);
    }

void Game::run() {
    while (m_window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }

        if (m_state == GameState::MAIN_MENU && event.type == sf::Event::MouseButtonPressed) {
            // Check for clicks on menu items
            if (m_startText.getGlobalBounds().contains(m_cursor.getPosition())) {
                m_state = GameState::PLAYING;
            } else if (m_exitText.getGlobalBounds().contains(m_cursor.getPosition())) {
                m_window.close();
            }
        }
    }
}

void Game::update() {
    m_cursor.update(m_window);

    if (m_state == GameState::MAIN_MENU) {
        // Highlight menu items based on cursor hover
        if (m_startText.getGlobalBounds().contains(m_cursor.getPosition())) {
            m_startText.setFillColor(sf::Color::Black);
        } else {
            m_startText.setFillColor(sf::Color::White);
        }

        if (m_exitText.getGlobalBounds().contains(m_cursor.getPosition())) {
            m_exitText.setFillColor(sf::Color::Black
























            );
        } else {
            m_exitText.setFillColor(sf::Color::White);
        }
    }
}

void Game::render() {
    m_window.clear(sf::Color::Black);

    if (m_state == GameState::MAIN_MENU) {
        renderMainMenu();
    }

    m_cursor.render(m_window);
    m_window.display();
}

void Game::renderMainMenu() {
    m_window.draw(m_titleText);
    m_window.draw(m_startText);
    m_window.draw(m_exitText);
}

} // namespace RatBoiGaming

#include "game.h"
#include "menu.h"
#include <iostream>

namespace RatBoiGaming {

    Game::Game(const std::string& title, int width, int height)
        : m_window(sf::VideoMode(width, height), title), m_state(GameState::MAIN_MENU), m_cursor(), m_menu(nullptr) {
        // Hide the system cursor
        m_window.setMouseCursorVisible(false);

        if (!m_font.loadFromFile("nunito.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            exit(-1);
        }

        // Initialize the main menu
        m_menu = std::make_unique<Menu>(m_font, width, height);

        // Load and configure the background music
        if (!m_backgroundMusic.openFromFile("Assets/Desolate-MM.wav")) {
            std::cerr << "Failed to load background music!" << std::endl;
            exit(-1);
        }
        m_backgroundMusic.setLoop(true);
        m_backgroundMusic.setVolume(50);
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

            if (m_state == GameState::MAIN_MENU) {
                int selectedOption = -1;
                m_menu->handleEvent(m_window, event, selectedOption);

                if (selectedOption == 0) { // New Game
                    m_state = GameState::PLAYING;
                    m_backgroundMusic.stop();
                } else if (selectedOption == 1) { // Load Save
                    std::cout << "Load Save selected\n";
                } else if (selectedOption == 2) { // Options
                    std::cout << "Options selected\n";
                } else if (selectedOption == 3) { // Exit
                    m_window.close();
                }
            }
        }
    }

    void Game::update() {
        if (m_state == GameState::MAIN_MENU) {
            if (m_backgroundMusic.getStatus() != sf::Music::Playing) {
                m_backgroundMusic.play();
            }
            m_menu->update(m_window);
        } else {
            if (m_backgroundMusic.getStatus() == sf::Music::Playing) {
                m_backgroundMusic.stop();
            }
            m_cursor.update(m_window); // Future gameplay update logic
        }
    }

    void Game::render() {
        m_window.clear(sf::Color::Black);

        if (m_state == GameState::MAIN_MENU) {
            m_menu->render(m_window);
        }

        m_cursor.render(m_window); // Render the cursor
        m_window.display();
    }

} // namespace RatBoiGaming


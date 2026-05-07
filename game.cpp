#include "game.h"
#include "menu.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

namespace RatBoiGaming {

    Game::Game(const std::string& title, int width, int height)
        : m_window(sf::VideoMode({static_cast<unsigned int>(width), static_cast<unsigned int>(height)}), title),
          m_font(),
          m_state(GameState::MAIN_MENU),
          m_menu(nullptr),
          m_backgroundMusic(),
          m_gameBackgroundTexture(),
          m_gameBackgroundSprite(m_gameBackgroundTexture),
          m_worldFloor(),
          m_player(),
          m_loadingText(m_font),
          m_helpText(m_font),
          m_playerSpeed(260.0f),
          m_windowWidth(width),
          m_windowHeight(height) {
        m_window.setMouseCursorVisible(false);
        m_window.setFramerateLimit(60);

        if (!m_font.openFromFile("nunito.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            std::exit(-1);
        }

        m_menu = std::make_unique<Menu>(m_font, static_cast<float>(width), static_cast<float>(height));

        if (!m_backgroundMusic.openFromFile("Assets/Desolate-MM.wav")) {
            std::cerr << "Failed to load background music!" << std::endl;
            std::exit(-1);
        }
        m_backgroundMusic.setLooping(true);
        m_backgroundMusic.setVolume(50.0f);

        if (!m_gameBackgroundTexture.loadFromFile("Assets/background.png")) {
            std::cerr << "Failed to load game background image!" << std::endl;
            std::exit(-1);
        }

        m_gameBackgroundSprite.setTexture(m_gameBackgroundTexture, true);
        m_gameBackgroundSprite.setScale({
            static_cast<float>(width) / static_cast<float>(m_gameBackgroundTexture.getSize().x),
            static_cast<float>(height) / static_cast<float>(m_gameBackgroundTexture.getSize().y)
        });
        m_gameBackgroundSprite.setColor(sf::Color(255, 255, 255, 150));

        m_worldFloor.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
        m_worldFloor.setFillColor(sf::Color(215, 225, 235));

        m_player.setRadius(28.0f);
        m_player.setOrigin({28.0f, 28.0f});
        m_player.setPosition({width / 2.0f, height / 2.0f});
        m_player.setFillColor(sf::Color(35, 55, 75));
        m_player.setOutlineColor(sf::Color::White);
        m_player.setOutlineThickness(4.0f);

        m_loadingText.setString("Loading Northern Shadows...");
        m_loadingText.setCharacterSize(44);
        m_loadingText.setFillColor(sf::Color::White);
        sf::FloatRect loadingBounds = m_loadingText.getLocalBounds();
        m_loadingText.setOrigin({
            loadingBounds.position.x + loadingBounds.size.x / 2.0f,
            loadingBounds.position.y + loadingBounds.size.y / 2.0f
        });
        m_loadingText.setPosition({width / 2.0f, height / 2.0f});

        m_helpText.setString("WASD / Arrow Keys: roam    Esc: menu");
        m_helpText.setCharacterSize(24);
        m_helpText.setFillColor(sf::Color::Black);
        m_helpText.setPosition({25.0f, 25.0f});
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
        while (const std::optional event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }

            if (m_state == GameState::MAIN_MENU) {
                int selectedOption = -1;
                m_menu->handleEvent(m_window, *event, selectedOption);

                if (selectedOption == 0) {
                    startNewGame();
                } else if (selectedOption == 1) {
                    std::cout << "Load Save selected\n";
                } else if (selectedOption == 2) {
                    std::cout << "Options selected\n";
                } else if (selectedOption == 3) {
                    m_window.close();
                }
            } else if (m_state == GameState::PLAYING) {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                if (keyPressed != nullptr && keyPressed->code == sf::Keyboard::Key::Escape) {
                    m_state = GameState::MAIN_MENU;
                    m_clock.restart();
                }
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

    void Game::startNewGame() {
        m_state = GameState::LOADING;
        m_backgroundMusic.stop();
        m_player.setPosition({m_windowWidth / 2.0f, m_windowHeight / 2.0f});
        m_loadingClock.restart();
        m_clock.restart();
    }

    void Game::update() {
        if (m_state == GameState::MAIN_MENU) {
            if (m_backgroundMusic.getStatus() != sf::Music::Status::Playing) {
                m_backgroundMusic.play();
            }
            m_menu->update(m_window);
            m_cursor.update(m_window);
        } else if (m_state == GameState::LOADING) {
            updateLoading();
        } else {
            updatePlaying();
        }
    }

    void Game::updateLoading() {
        m_cursor.update(m_window);

        if (m_loadingClock.getElapsedTime().asSeconds() >= 1.0f) {
            m_state = GameState::PLAYING;
            m_clock.restart();
        }
    }

    void Game::updatePlaying() {
        float dt = m_clock.restart().asSeconds();
        sf::Vector2f move(0.0f, 0.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            move.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            move.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            move.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            move.x += 1.0f;
        }

        if (move.x != 0.0f || move.y != 0.0f) {
            float length = std::sqrt((move.x * move.x) + (move.y * move.y));
            move /= length;
            m_player.move(move * m_playerSpeed * dt);
            keepPlayerInBounds();
        }

        m_cursor.update(m_window);
    }

    void Game::keepPlayerInBounds() {
        sf::Vector2f pos = m_player.getPosition();
        float r = m_player.getRadius();

        if (pos.x < r) {
            pos.x = r;
        }
        if (pos.x > m_windowWidth - r) {
            pos.x = m_windowWidth - r;
        }
        if (pos.y < r) {
            pos.y = r;
        }
        if (pos.y > m_windowHeight - r) {
            pos.y = m_windowHeight - r;
        }

        m_player.setPosition(pos);
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
        } else if (m_state == GameState::LOADING) {
            renderLoading();
        } else {
            renderPlaying();
        }

        m_cursor.render(m_window);
        m_window.display();
    }

    void Game::renderLoading() {
        m_window.draw(m_gameBackgroundSprite);
        m_window.draw(m_loadingText);
    }

    void Game::renderPlaying() {
        m_window.draw(m_worldFloor);
        m_window.draw(m_gameBackgroundSprite);
        m_window.draw(m_player);
        m_window.draw(m_helpText);
    }

} // namespace RatBoiGaming
        }

        m_cursor.render(m_window); // Render the cursor
        m_window.display();
    }

} // namespace RatBoiGaming


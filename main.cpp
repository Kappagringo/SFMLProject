#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

int main() {
    // Create the main SFML window.
    sf::RenderWindow render_window(sf::VideoMode(800, 600), "SFGUI Example");

    // Create an SFGUI object (used to draw our GUI).
    sfg::SFGUI sfgui;

    // Create a simple SFGUI window widget.
    auto window = sfg::Window::Create();
    window->SetTitle("Hello, SFGUI!");

    // Create a label and add it to that window.
    auto label = sfg::Label::Create("Hello, SFGUI!");
    window->Add(label);

    // Create a desktop and add our SFGUI window to it.
    sfg::Desktop desktop;
    desktop.Add(window);

    // A clock to measure the elapsed time each frame (for SFGUI updates).
    sf::Clock clock;

    // Main loop.
    while (render_window.isOpen()) {
        // Handle SFML events (keyboard, mouse, closing, etc.).
        sf::Event event;
        while (render_window.pollEvent(event)) {
            // Forward events to SFGUI.
            desktop.HandleEvent(event);

            // Close the window if the user requests it.
            if (event.type == sf::Event::Closed) {
                render_window.close();
            }
        }

        // Calculate the elapsed time since last frame.
        sf::Time delta = clock.restart();

        // Update the GUI with the elapsed time (necessary for animations, etc.).
        desktop.Update(delta.asSeconds());

        // Clear the window (background).
        render_window.clear();

        // Let SFGUI draw its widgets onto our SFML render_window.
        sfgui.Display(render_window);

        // Finally, display the updated frame.
        render_window.display();
    }

    return 0;
}

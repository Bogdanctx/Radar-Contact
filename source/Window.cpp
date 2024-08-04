#include "Window.hpp"

Window::Window(int width, int height) :
                m_window(sf::VideoMode(width, height), "Radar Contact", sf::Style::Close | sf::Style::Titlebar)
{
    m_window.setFramerateLimit(60);
    m_appIcon.loadFromFile("./resources/general_textures/icon.png");
    m_window.setIcon(32, 32, m_appIcon.getPixelsPtr());
}

void Window::run() {

    while(m_window.isOpen()) {
        handleEvent();
        update();
        render();
    }

}

void Window::render() {
    m_window.clear();

    m_window.display();
}

void Window::handleEvent() {
    sf::Event window_event{};

    while(m_window.pollEvent(window_event)) {
        switch(window_event.type) {
            case sf::Event::Closed: {
                m_window.close();
                break;
            }

            default:
                break;
        }
    }
}
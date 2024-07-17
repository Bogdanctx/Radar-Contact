#include "../header/Window.h"

Window::Window(const std::pair<int, int> resolution, const std::string &title) :
                m_window(sf::VideoMode(resolution.first, resolution.second), title,
                         sf::Style::Close | sf::Style::Titlebar)
{
    m_window.setFramerateLimit(60);
    m_appIcon.loadFromFile("./resources/general_textures/radar.png");
    m_window.setIcon(512, 512, m_appIcon.getPixelsPtr());
}

void Window::run() {

    while(m_window.isOpen())
    {
        handleEvent();
        update();
        render();
    }

}

void Window::render() {
    m_window.clear();

    m_window.display();
}

void Window::handleEvent()
{
    sf::Event window_event{};

    while(m_window.pollEvent(window_event))
    {
        switch(window_event.type)
        {
            case sf::Event::Closed:
            {
                m_window.close();
                break;
            }

            default:
                break;
        }
    }
}
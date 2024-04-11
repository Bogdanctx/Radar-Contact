//
// Created by bgd on 09.04.2024.
//

#include "../header/Window.h"

Window::Window(const std::pair<int, int> resolution, const std::string &title) :
                m_window(sf::VideoMode(resolution.first, resolution.second), title)
{
    m_window.setVerticalSyncEnabled(true);
}

void Window::run() {

    while(m_window.isOpen())
    {
        handleEvent();
        update();
        render();
    }

}

void Window::update()
{

}

void Window::render()
{
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
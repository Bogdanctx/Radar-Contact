#pragma once

#include <SFML/Graphics.hpp>

#include <utility>

class Window {
public:
    Window() = delete;
    Window(int width, int height);
    virtual ~Window() = default;

    virtual void run();

protected:
    sf::RenderWindow m_window;

private:
    virtual void handleEvent() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

private:
    sf::Image m_appIcon;
};

#pragma once

#include <SFML/Graphics.hpp>

class AppWindow {
public:
    AppWindow() = delete;
    AppWindow(int width, int height);
    virtual ~AppWindow() = default;

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

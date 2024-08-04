#pragma once

#include <SFML/Graphics.hpp>

#include <utility>
#include <memory>

class Window {
public:
    Window() = delete;
    Window(std::pair<int, int> resolution, const std::string &title);
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

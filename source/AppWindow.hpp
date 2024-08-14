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
    sf::View m_view;

    sf::Vector2f positionRelativeToView(sf::Vector2f position) const;
    sf::Vector2f positionRelativeToView(sf::Vector2i position) const;

    void updateWindowView(int width, int height);

private:
    virtual void handleEvent() = 0;
    virtual void update() = 0;
    virtual void render() = 0;


    sf::Image m_appIcon;
};

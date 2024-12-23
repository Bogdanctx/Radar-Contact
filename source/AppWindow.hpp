#pragma once

#include <SFML/Graphics.hpp>

class AppWindow {
public:
    AppWindow() = delete;
    AppWindow(unsigned int width, unsigned int height);
    virtual ~AppWindow() = default;

    virtual void run();

protected:
    sf::RenderWindow m_window;

    sf::Vector2f positionRelativeToView(sf::Vector2f position) const;
    sf::Vector2f positionRelativeToView(sf::Vector2i position) const;

    virtual void internalHandleEvent(const std::optional<sf::Event>& event) = 0;
    virtual void internalRender() = 0;
    virtual void internalUpdate() = 0;

private:
    void handleEvent();
    void update();
    void render();
    void updateWindowView(unsigned int width, unsigned int height);

    sf::Image m_appIcon;
    sf::View m_view;

};

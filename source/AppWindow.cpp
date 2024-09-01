#include "AppWindow.hpp"

AppWindow::AppWindow(int width, int height) :
                m_window(sf::VideoMode(width, height), "Radar Contact")
{
    m_window.setFramerateLimit(60);
    m_appIcon.loadFromFile("./resources/general_textures/icon.png");
    m_window.setIcon(32, 32, m_appIcon.getPixelsPtr());

    m_view.setSize(width, height);
    m_view.setCenter( m_view.getSize().x / 2, m_view.getSize().y / 2);
    updateWindowView(width, height);
}

sf::Vector2f AppWindow::positionRelativeToView(sf::Vector2f position) const
{
    return m_window.mapPixelToCoords(static_cast<sf::Vector2i>(position), m_window.getView());
}

sf::Vector2f AppWindow::positionRelativeToView(sf::Vector2i position) const
{
    return m_window.mapPixelToCoords(position, m_window.getView());
}


// https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view
void AppWindow::updateWindowView(unsigned int width, unsigned int height)
{
    float windowRatio = static_cast<float>(width) / static_cast<float>(height);
    float viewRatio = m_view.getSize().x / m_view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    m_view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    m_window.setView(m_view);
}


void AppWindow::run() {

    while(m_window.isOpen()) {
        handleEvent();
        update();
        render();
    }

}

void AppWindow::update()
{
    internalUpdate();
}

void AppWindow::render() {
    m_window.clear();

    internalRender();

    m_window.display();
}

void AppWindow::handleEvent() {
    sf::Event event{};

    while(m_window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed: {
                m_window.close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                sf::Keyboard::Key key = event.key.code;

                if(key == sf::Keyboard::Escape)
                {
                    m_window.close();
                }

                break;
            }
            case sf::Event::Resized:
            {
                updateWindowView(event.size.width, event.size.height);

                break;
            }
            default:
                break;
        }

        internalHandleEvent(event);
    }
}
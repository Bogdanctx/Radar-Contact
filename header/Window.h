//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_WINDOW_H
#define OOP_WINDOW_H

#include <SFML/Graphics.hpp>

class Window {
public:
    explicit Window(std::pair<int, int> resolution, const std::string &title);
    ~Window() = default;

    virtual void run();
protected:
    sf::RenderWindow m_window;
private:
    virtual void handleEvent();
    virtual void update();
    virtual void render();
};


#endif //OOP_WINDOW_H

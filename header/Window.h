//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_WINDOW_H
#define OOP_WINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Window {
public:
    explicit Window(int width, int height, const std::string &title);
    ~Window() { std::cout << "Destr Window\n"; }

    void run();
protected:
    sf::RenderWindow m_window;
private:
    virtual void handleEvent();
    virtual void update();
    virtual void render();
};


#endif //OOP_WINDOW_H

//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>

class Game {
public:
    Game() = delete;
    explicit Game(int width, int height);
    ~Game() = default;

    void run();

private:

    void handleEvents();
    void update();
    void render();

    sf::RenderWindow m_window;
};


#endif //OOP_GAME_H

//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Window.h"
#include "Airplane.h"
#include "ResourcesManager.h"

class Game : public Window {
public:
    explicit Game(ResourcesManager *resourcesManager);
    ~Game() { std::cout<<"Destr Game\n"; };

private:
    void render() override;
    void handleEvent() override;
    void update() override;

    std::vector<Airplane> m_airplanes;
    ResourcesManager *m_resourcesManager;
};


#endif //OOP_GAME_H

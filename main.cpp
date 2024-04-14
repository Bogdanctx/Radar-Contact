#include "./header/Menu.h"
#include "./header/Game.h"
#include "./header/ResourcesManager.h"

int main() {
    ResourcesManager resourcesManager;

    {
        //Menu menu{resourcesManager};

        //menu.run();
    }

    Game game{resourcesManager};
    game.run();

    return 0;
}

#include "./header/Menu.h"
#include "./header/Game.h"
#include "./header/ResourcesManager.h"

int main() {
    ResourcesManager resourcesManager;

    {
        Menu menu{&resourcesManager};

        menu.run();
    }

    if(resourcesManager.getResolution().first == 0) {
        return 0;
    }

    Game game{resourcesManager};
    game.run();

    return 0;
}

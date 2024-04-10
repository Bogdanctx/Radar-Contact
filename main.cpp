#include "./header/Menu.h"
#include "./header/Game.h"

int main() {
    std::pair<int, int> game_resolution{0, 0};

    {
        Menu menu{&game_resolution};

        menu.run();
    }

    if(game_resolution.first != 0 && game_resolution.second != 0) {
        Game game{game_resolution.first, game_resolution.second};
        game.run();
    }

    return 0;
}

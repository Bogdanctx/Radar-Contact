/*
 * TO DO LIST
 *
8. Event-uri random pentru emergency-uri pentru avioane si elicoptere
	-> Avioanele pot avea emergency-uri de tipul alarma cu bomba, engine fire, sanatate pacient
	-> Emergency-uri elicoptere: Engine fire (si sa isi schimbe de multe ori directia si sa
	scada rapid in altitudine)

*/

#include "./header/Menu.h"
#include "./header/Game.h"

int main() {
    srand(time(nullptr));

    try {
        ResourcesManager::Instance().load();
    } catch(ErrorResourcesManager &err) {
        std::cout<<err.what();
        return 0;
    }

    Menu menu;
    menu.run();

    if(ResourcesManager::Instance().getSelectedRegion().empty()) {
        return 0;
    }

    Game game;
    game.run();

    return 0;
}

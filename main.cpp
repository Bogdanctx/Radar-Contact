/*
 * TO DO LIST
 *
8. Event-uri random pentru emergency-uri pentru avioane si elicoptere
	-> Avioanele pot avea emergency-uri de tipul alarma cu bomba, engine fire, sanatate pacient
	-> Emergency-uri elicoptere: Engine fire (si sa isi schimbe de multe ori directia si sa
	scada rapid in altitudine)
10. De adaugat Canada, Austria, Turkey

*/

#include "./header/Menu.h"
#include "./header/Game.h"

int main() {
    srand(time(nullptr));
    ResourcesManager::Instance().load();

    {
        //Menu menu{resourcesManager};

        //menu.run();
    }

    Game game;
    game.run();

    return 0;
}

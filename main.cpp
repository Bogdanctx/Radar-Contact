/*
 * TO DO LIST
 *
1. De facut ca avioanele sa se miste separat de elicoptere
3. Detectie coliziuni intre avioane si elicoptere
4. Sa poti modifica altitudinea si viteza entitatilor
5. Sa poti schimba directia entitatilor
6. Cand avioanele intra in raza de acoperire a unui aeroport sa dispara de pe harta
7. Pusa limita de avioane per aeroport
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

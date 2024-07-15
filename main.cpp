/* TO DO

-> Event-uri random pentru emergency-uri pentru avioane si elicoptere
	-> Avioanele pot avea emergency-uri de tipul alarma cu bomba, engine fire, sanatate calator
	-> Emergency-uri elicoptere: Engine fire (si sa isi schimbe de multe ori directia si sa
	scada rapid in altitudine)
si in anumite cazuri entitatile sa aibe un timp pana la prabusire => pot fi preluate de orice aeroport din apropiere
 etc...

-> De adaugat un mini-chat care sa afiseze mereu ultimele 4-5 instructiuni date tuturor entitatilor (e.g.: RYR512 turn
 to heading {newHeading}; ROT125 set speed to 180kts) si mesajele transmise de entitati in cazul emergency-urilor
 (e.g.: WZZ1MK declares engine fire; si sa apara textul cu rosu)

*/

#include "./header/ResourcesManager.h"
#include "./header/StateMachine.h"

int main() {
    try {

        ResourcesManager::Instance().load();
        StateMachine::Instance().run();

    } catch(ErrorResourcesManager &err) {
        std::cout << err.what();
    }

    return 0;
}

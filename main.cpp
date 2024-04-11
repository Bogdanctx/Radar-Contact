#include "./header/Menu.h"
#include "./header/Game.h"
#include "./header/ResourcesManager.h"

int main() {
    /*cpr::Response r = cpr::Get(cpr::Url{"https://api.aviationapi.com/v1/vatsim/pilots?apt=EGLL&arr=1&dep=0"},
                               cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                               cpr::Parameters{{"anon", "true"}, {"key", "value"}});
    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    nlohmann::json data = nlohmann::json::parse(r.text);

    int n = data["EGLL"].size();

    for(int i = 0; i < n; i++) {
        std::cout<<data["EGLL"][i]["callsign"]<<'\n';
    }

    return 0;*/

    ResourcesManager resourcesManager;

    {
        Menu menu{&resourcesManager};

        menu.run();
    }

    if(resourcesManager.GetResolution().first == 0) {
        return 0;
    }

    Game game{&resourcesManager};
    game.run();

    return 0;
}

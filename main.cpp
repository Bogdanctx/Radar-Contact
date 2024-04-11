#include "./header/Menu.h"
#include "./header/Game.h"

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

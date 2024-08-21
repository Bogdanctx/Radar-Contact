#pragma once

#include "LiveAPI.hpp"

#include <nlohmann/json.hpp>

class MockAPI : public LiveAPI {
public:
    explicit MockAPI(const Region& region) : LiveAPI(region) {}

    nlohmann::json downloadFlyingEntities() override;
    void downloadWeatherTextures() override;
};

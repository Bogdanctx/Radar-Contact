#pragma once

#include "AppWindow.hpp"

#include <memory>
#include <queue>

class StateMachine {
public:
    StateMachine(const StateMachine&) = delete;
    StateMachine operator=(const StateMachine&) = delete;

    static StateMachine& Instance();

    void run();
    void pushState(const std::shared_ptr<AppWindow>& window);

private:
    StateMachine();

private:
    std::shared_ptr<AppWindow> m_currentState;
    std::queue<std::shared_ptr<AppWindow>> m_states;
};
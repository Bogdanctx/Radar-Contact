#pragma once

#include "Window.hpp"

#include <memory>
#include <stack>

class StateMachine {
public:
    StateMachine(const StateMachine&) = delete;
    StateMachine operator=(const StateMachine&) = delete;

    static StateMachine& Instance();

    void run();
    void pushState(const std::shared_ptr<Window>& window);

private:
    StateMachine();

private:
    std::shared_ptr<Window> m_currentState;
    std::stack<std::shared_ptr<Window>> m_states;
};
#include "StateMachine.hpp"
#include "Menu.hpp"
#include "Game.hpp"

StateMachine::StateMachine() {
    std::shared_ptr<AppWindow> state = std::make_shared<Menu>();
    m_states.push(state);
}

StateMachine& StateMachine::Instance() {
    static StateMachine instance;
    return instance;
}

void StateMachine::run() {
    while(!m_states.empty()) {
        m_currentState = m_states.front();
        m_states.pop();

        m_currentState->run();
    }
}

void StateMachine::pushState(const std::shared_ptr<AppWindow>& window) {
    m_states.push(window);
}
#include "../header/StateMachine.h"
#include "../header/Menu.h"
#include "../header/Game.h"

StateMachine::StateMachine() {
    std::shared_ptr<Window> state = std::make_shared<Menu>();
    m_states.push(state);
}

StateMachine& StateMachine::Instance() {
    static StateMachine instance;
    return instance;
}

void StateMachine::run() {
    while(!m_states.empty()) {
        m_currentState = m_states.top();
        m_states.pop();

        m_currentState->run();

        if(std::dynamic_pointer_cast<Menu>(m_currentState)) {
            if(ResourcesManager::Instance().getSelectedRegion().empty()) { // if game has been closed in menu
                break;
            }
        }

    }
}

void StateMachine::pushState(const std::shared_ptr<Window>& window) {
    m_states.push(window);
}
//
// Created by bgd on 18.06.2024.
//

#ifndef OOP_STATEMACHINE_H
#define OOP_STATEMACHINE_H

#include "Window.h"

#include <memory>
#include <stack>

class StateMachine {
public:
    StateMachine(const StateMachine&) = delete;
    StateMachine operator=(const StateMachine&) = delete;

    static StateMachine& Instance() {
        static StateMachine instance;
        return instance;
    }

    void run();
    void pushState(const std::shared_ptr<Window>& window);

private:
    StateMachine();

    std::shared_ptr<Window> m_currentState;
    std::stack<std::shared_ptr<Window>> m_states;
};


#endif //OOP_STATEMACHINE_H

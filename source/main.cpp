#include "ResourcesManager.hpp"
#include "StateMachine.hpp"

int main() {
    try {
        ResourcesManager::Instance().load();
        StateMachine::Instance().run();
    } catch(ErrorResourcesManager &err) {
        std::cout << err.what();
    }
}

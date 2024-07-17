#include "./header/ResourcesManager.h"
#include "./header/StateMachine.h"

int main() {
    try {
        ResourcesManager::Instance().load();
        StateMachine::Instance().run();
    } catch(ErrorResourcesManager &err) {
        std::cout << err.what();
    }
}

#include <iostream>

#include "ResourcesManager.hpp"
#include "StateMachine.hpp"

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////

int main() {
    ////////////////////////////////////////////////////////////////////////
    /// NOTE: this function call is needed for environment-specific fixes //
    init_threads();                                                       //
    ////////////////////////////////////////////////////////////////////////

    try {
        ResourcesManager::Instance().load();
        StateMachine::Instance().run();
    } catch(std::runtime_error &err) {
        std::cout << err.what();
    }
}

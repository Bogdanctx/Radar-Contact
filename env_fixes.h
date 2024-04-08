//
// Created by marius on 02.02.2024.
//

#ifndef OOP_ENV_FIXES_H
#define OOP_ENV_FIXES_H

#ifdef __linux__
#include <X11/Xlib.h>
#endif

void init_threads() {
#ifdef __linux__
    XInitThreads();
#endif
}

#endif //OOP_ENV_FIXES_H

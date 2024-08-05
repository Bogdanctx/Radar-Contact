//
// Created by marius on 02.02.2024.
//
#pragma once

#ifdef __linux__
#include <X11/Xlib.h>
#endif

void init_threads() {
#ifdef __linux__
    XInitThreads();
#endif
}

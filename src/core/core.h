/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Author: Mateus Silva
 * -----------------------------------------
 */

#pragma once

#ifndef core_h
    #define core_h

    using namespace std;

    #include "window.h"
    #include "sound.h"

    namespace core
    {
        /**
        * @brief Initializes and runs the main game loop.
        *
        * This function configures the game window, initializes the map and keyboard and player.
        *
        * @param argc Number of command line arguments.
        * @param argv Array of strings containing the command line arguments.
        */
        void run(int argc, char* argv[]);
    }

#endif /* core_h */
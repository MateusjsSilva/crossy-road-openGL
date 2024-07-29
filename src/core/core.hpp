/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Authors: Mateus Silva, Jailson Palhares
 * -----------------------------------------
 */

#pragma once

#ifndef core_hpp
	#define core_hpp

	#include "graphic/window.hpp"
	#include "gameplay/keyboard.hpp"
	#include "gameplay/map.hpp"

	namespace core 
	{
		/**
		* @brief Initializes and runs the main game loop.
		*
		* This function configures the game window, initializes the map and keyboard,
		* and starts the main OpenGL loop for continuous rendering.
		*
		* @param argc Number of command line arguments.
		* @param argv Array of strings containing the command line arguments.
		*/
        void run(int argc, char* argv[])
        {
			// initialize the window
			gameWindow game_window = gameWindow(argc, argv);
			game_window.setConfig("Frogger + Crossy Road", 900, 650);
			game_window.init(100, 100);

			// initialize the map
			gameMap game_map = gameMap();

			// initialize the keyboard
			gameKeyboard game_keyboard = gameKeyboard();

			game_window.glutLoop();
        }
	}

#endif /* core_hpp */
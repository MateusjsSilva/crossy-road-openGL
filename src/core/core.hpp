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
	#include "gameplay/objects/car.hpp"

	namespace core {

		void init(int argc, char* argv[]) 
        {
			glutInit(&argc, argv);
		}

        void run() 
        {
			window gameWindow = window("Frogger + Crossy Road", 900, 500);
			gameWindow.init(100, 100);

        }
	}

#endif /* core_hpp */
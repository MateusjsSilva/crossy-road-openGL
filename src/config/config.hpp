/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Authors: Mateus Silva, Jailson Palhares
 * -----------------------------------------
 */

#pragma once

#ifndef config_hpp
	#define config_hpp

	#ifdef __APPLE__ // MacOS
		#define GL_SILENCE_DEPRECATION
		#include <GLUT/glut.h>
		#include <OpenGL/gl.h>
		#include <OpenGL/glu.h>
	#else // Windows e Linux
		#include <GL/glut.h>
		#include <GL/gl.h>
		#include <GL/glu.h>
	#endif

	// Include other libraries
	#include <cmath>
	#include <random>
	#include <iostream>
	#include <cstdlib>
	#include <map>

	// Define PI if not already defined
	#ifndef M_PI
		#define M_PI 3.14159265358979323846 
	#endif

	// Define ESC key code if not already defined
	#ifndef ESC
		#define ESC 27 
	#endif

	// Define SPACE key code if not already defined
	#ifndef SPACE
		#define SPACE 32
	#endif

	using namespace std;

#endif /* config_hpp */
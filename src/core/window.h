/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Author: Mateus Silva
 * -----------------------------------------
 */

#pragma once

#ifndef window_h
	#define window_h

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

    #include "sound.h"
    #include "include/glm.h"
    #include "gameplay/player.h"
    #include "gameplay/car.h"
    #include <fstream>
    #include <iostream>
    #include <sstream>
    #include <cstdio>
    #include <cmath>
    #include <map>

    #define ESC 27 
    #define SPACE 32
    #define MAX_FPS 70
    #define FPS 60
    #define KEYFRAME_RATE 3

    void initGlut(const char* title, int argc, char** argv);
    void reshape(int w, int h);
    void display(void);
    void drawAnimation(int type, GLuint mode);

    void timer(int value);
    void keyboard(unsigned char key, int x, int y);
    void keyboard_special(int key, int x, int y);

    void generateCars();
    bool loadLevel();
    void loadPlayerAnimations();
    void renderGrass();
    void renderRoad(float x, float z);
    void renderWater(float x, float z);
    void renderTree(float x, float z);
    void renderLilypad(float x, float z);
    void renderFinishLine(float x, float z);
    void generateCars();
    void renderGrid();
    void renderPlayer(float x, float z, GLuint mode, int playerDirection, bool isJumping, float jumpStartTime, float jumpDuration);

    void death();
    void victory();

#endif /* window_h */
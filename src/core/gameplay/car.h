/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Author: Mateus Silva
 * -----------------------------------------
 */

#pragma once

#ifndef car_h
    #define car_h

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

    #include <cstdlib>
    #include <ctime>

    class Car 
    {
        public:
            float x, y, z;
            float speed;
            int direction;
            int road;
            int type;

            Car(float startX, float startY, float startZ, float spd, int dir, int rd);
            bool update(int w1,int w2, float playerX, float playerZ, int playerGridX, int playerGridZ);
            void draw();
    };

#endif /* car_h */
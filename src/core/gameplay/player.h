/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Author: Mateus Silva
 * -----------------------------------------
 */

#pragma once

#ifndef player_h
	#define player_h
    
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

    #include "../window.h"

	class Player
	{
        public:

            int level = 1;

            // Position and Movement
            float posX = 0.0f;
            float posY = 0.0f;
            float posZ = 0.0f;
            float speed = 0.0f;

            // State
            bool canJump = true;
            bool isJumping = false;
            bool isDead = false;
            bool hasWon = false;

            // Grid Position
            int playerGridX = 0;
            int playerGridZ = 0;
            int playerDirection = 1;

            // jump
            float jumpStartTime;
            float jumpDuration = 0.3f;

            int timerW = 0;
            int timerD = 0;

            // Constructors
            Player();

            // Movement Methods
            void moveUp(const std::vector<std::vector<char>>& levelData);
            void moveDown(const std::vector<std::vector<char>>& levelData);
            void moveLeft(const std::vector<std::vector<char>>& levelData);
            void moveRight(const std::vector<std::vector<char>>& levelData);

            // Collision Detection
            void checkCollision(const std::vector<std::vector<char>>& levelData);
            void setPosition(float x, float y, float z);

            // Drawing Methods
            void drawOrientationLines(float length);
            void death();
            void victory();
    };

#endif /* player_h */
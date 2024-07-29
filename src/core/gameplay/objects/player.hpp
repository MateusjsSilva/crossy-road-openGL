/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Authors: Mateus Silva, Jailson Palhares
 * -----------------------------------------
 */

#pragma once

#ifndef player_hpp
	#define player_hpp

	#include "../events.hpp"

	class player : public events
	{
		public:

			void keyboard(unsigned char key, int x, int y) 
			{
                switch (key) {

                case GLUT_KEY_UP:

                    if (canJump == true)
                    {
                        switch (listOfRows[playerRelativeToGridZ - 1][playerRelativeToGridX])
                        {
                        case '1':
                            break;
                        default:
                            finalZ = gameZ + 4;
                            playerDirection = 1;
                            canJump = false;
                            playerRelativeToGridZ -= 1;
                            break;
                        }

                    }
                    break;

                case GLUT_KEY_LEFT:

                    if (canJump == true && playerRelativeToGridX > 0)
                    {
                        switch (listOfRows[playerRelativeToGridZ][playerRelativeToGridX - 1]) {
                        case '1':
                            break;

                        default:
                            finalX = gameX + 4;
                            playerDirection = 2;
                            canJump = false;
                            playerRelativeToGridX -= 1;
                            break;
                        }

                    }
                    break;

                case GLUT_KEY_RIGHT:

                    if (canJump == true && playerRelativeToGridX < 15)
                    {
                        switch (listOfRows[playerRelativeToGridZ][playerRelativeToGridX + 1]) {
                        case '1':
                            break;

                        default:
                            finalX = gameX - 4;
                            playerDirection = 0;
                            canJump = false;
                            playerRelativeToGridX += 1;
                            break;
                        }
                    }
                    break;

                case GLUT_KEY_DOWN:

                    if (canJump == true && playerRelativeToGridZ < 31)
                    {
                        switch (listOfRows[playerRelativeToGridZ + 1][playerRelativeToGridX]) {
                        case '1':
                            break;

                        default:
                            finalZ = gameZ - 4;
                            playerDirection = 3;
                            canJump = false;
                            playerRelativeToGridZ += 1;
                            break;
                        }
                    }
                    break;
                }

                glutPostRedisplay();
			}
		private:
	};

#endif /* player_hpp */
/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Authors: Mateus Silva, Jailson Palhares
 * -----------------------------------------
 */

#pragma once

#ifndef window_hpp
	#define window_hpp

	class window {
		public:
            window(const char* title, int width, int height) {
                this -> title = title;
                this -> height = height;
                this -> width = width;
            }

            void init(int posX, int posY)
            {
                glutInitWindowPosition(posX, posY);
                glutInitWindowSize(this -> width, this -> height);
                glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
                glutCreateWindow(this -> title);

                glEnable(GL_DEPTH_TEST);

                // Register callbacks
                glutDisplayFunc(this -> display);
                glutReshapeFunc(this -> reshape);
            }

            void glutLoop() 
            {
                glutMainLoop();
            }

		private:
			static int fps;
			int height, width;
            const char* title;
			
            static void display() 
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity();


                glutSwapBuffers();
            }

            static void reshape(int width, int height) 
            {
                if (height == 0) // Prevent a divide by zero
                    height = 1;
                float ratio = 1.0 * width / height;

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glViewport(0, 0, width, height);
                gluPerspective(30, ratio, 1, 1000);
                glMatrixMode(GL_MODELVIEW);
            }
	};

#endif /* window_hpp */
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

    #include "../gameplay/events.hpp"

	class gameWindow 
    {
		public:
            gameWindow(int argc, char* argv[])
            {
                glutInit(&argc, argv);
            }

            void setConfig(const char* title, int width, int height) 
            {
                this->title = title;
                this->height = height;
                this->width = width;
            }

            void init(int posX, int posY)
            {
                glutInitWindowPosition(posX, posY);
                glutInitWindowSize(this -> width, this -> height);
                glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
                glutCreateWindow(this -> title);

                glEnable(GL_DEPTH_TEST);

                // Register callbacks
                glutReshapeFunc(this -> reshape);

                //glutTimerFunc(1000 / fps, this -> timer, 0);

                GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
                GLfloat mat_shininess[] = { 100.0 };
                GLfloat light_position[] = { 0.0, 30.0, -15.0, 0.0 };
                GLfloat light_ambient[] = { 0.6, 0.6, 0.6, 1.0 };

                glShadeModel(GL_SMOOTH);

                glMaterialfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
                glMaterialfv(GL_LIGHT0, GL_SHININESS, mat_shininess);
                glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
                glLightfv(GL_LIGHT0, GL_POSITION, light_position);

                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
                glEnable(GL_DEPTH_TEST);

                glEnable(GL_COLOR_MATERIAL);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                // Set the clear color
                glClearColor(38 / 256.0, 166 / 256.0, 91 / 256.0, 0.0);

                // Set the fill color
                glColor3f(1.0, 1.0, 1.0);

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(30, 1.333333, 0.1, 1000);

                // Fog color
                glClearColor(0.5, 0.5, 0.5, 1.0);
            }

            void glutLoop() 
            {
                glutMainLoop();
            }

		private:
			static int fps;
			int height, width;
            const char* title;
            static vector<events*> listEvents;

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

            static void timer(int value) {
                for (auto event : listEvents)
                    event -> timer(value);
                glutTimerFunc(1000 / fps, timer, 0);
                glutPostRedisplay();
            }
	};

    int gameWindow::fps = 60;
    vector<events*> gameWindow::listEvents = vector<events*>();

#endif /* window_hpp */
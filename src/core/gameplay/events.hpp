/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Authors: Mateus Silva, Jailson Palhares
 * -----------------------------------------
 */

#pragma once

#ifndef events_hpp
	#define events_hpp

    class events {
        public:
            virtual void display() {}
            virtual void timer(int value) {}
            virtual void keyboard(unsigned char key, int x, int y) {}
            virtual void specialKeys(int key, int x, int y) {}
            virtual void mouse(int button, int state, int x, int y) {}
    };

#endif /* events_hpp */
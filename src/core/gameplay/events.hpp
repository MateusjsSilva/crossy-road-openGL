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

    /**
    * @brief Abstract base class for handling game events.
    *
    * This class provides virtual methods for handling various types of game events.
    * Derived classes should override these methods to implement specific event handling.
    */
    class events 
    {
        public:
            /**
            * @brief Virtual method for rendering the display.
            *
            * This method should be overridden to define how the game state is drawn to the screen.
            */
            virtual void display() {}

            /**
            * @brief Virtual method for handling keyboard input.
            *
            * @param key The ASCII code of the key that was pressed.
            * @param x The x-coordinate of the mouse at the time of the key press.
            * @param y The y-coordinate of the mouse at the time of the key press.
            *
            * This method should be overridden to define how keyboard input is processed.
            */
            virtual void keyboard(unsigned char key, int x, int y) {}

            /**
            * @brief Virtual method for handling mouse input.
            *
            * @param button The mouse button that was pressed or released.
            * @param state The state of the mouse button (GLUT_DOWN or GLUT_UP).
            * @param x The x-coordinate of the mouse at the time of the button press/release.
            * @param y The y-coordinate of the mouse at the time of the button press/release.
            *
            * This method should be overridden to define how mouse input is processed.
            */
            virtual void mouse(int button, int state, int x, int y) {}

            /**
            * @brief Virtual method for handling special keyboard input.
            *
            * @param key The identifier for the special key that was pressed (e.g., GLUT_KEY_LEFT).
            * @param x The x-coordinate of the mouse at the time of the key press.
            * @param y The y-coordinate of the mouse at the time of the key press.
            *
            * This method should be overridden to define how special keys (e.g., arrow keys) are processed.
            */
            virtual void specialKeys(int key, int x, int y) {}

            /**
            * @brief Virtual method for handling timer events.
            *
            * @param value The timer value passed to the callback.
            *
            * This method should be overridden to define actions to be performed on timer events.
            */
            virtual void timer(int value) {}

            /**
            * @brief Virtual method for updating the game state.
            *
            * This method should be overridden to define how the game state is updated.
            */
            virtual void update() {}
    };

#endif /* events_hpp */
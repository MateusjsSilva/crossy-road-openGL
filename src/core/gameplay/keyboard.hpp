/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Authors: Mateus Silva, Jailson Palhares
 * -----------------------------------------
 */

#pragma once

#ifndef keyboard_hpp
    #define keyboard_hpp

    /**
    * @brief Class for managing keyboard input events.
    *
    * This class registers callback functions with GLUT for handling keyboard input.
    * It maintains a list of event handlers that are notified when keyboard events occur.
    */
    class gameKeyboard 
    {
        public:
            /**
            * @brief Constructor for the keyboard class.
            *
            * Registers static callback functions with GLUT for keyboard input handling.
            */
            gameKeyboard() {
                glutKeyboardFunc(this -> keyboardFunc);
                glutSpecialFunc(this -> specialKeys);
            }

            /**
            * @brief Add a new event handler to the list of events.
            *
            * @param event Reference to an event object that will handle keyboard input.
            */
            void addEvent(events& event) {
                listEvents.push_back(&event);
            }
        
        private:
            static vector<events*> listEvents;

            /**
            * @brief Static callback function for handling regular keyboard keys.
            *
            * @param key The ASCII code of the key that was pressed.
            * @param x The x-coordinate of the mouse at the time of the key press.
            * @param y The y-coordinate of the mouse at the time of the key press.
            *
            * Calls the `keyboard` method of each event handler in the list.
            */
            static void keyboardFunc(unsigned char key, int x, int y) {
                for (auto event : listEvents)
                    event-> keyboard(key, x, y);
            }

            /**
            * @brief Static callback function for handling special keys (e.g., arrow keys).
            *
            * @param key The identifier for the special key that was pressed.
            * @param x The x-coordinate of the mouse at the time of the key press.
            * @param y The y-coordinate of the mouse at the time of the key press.
            *
            * Calls the `specialKeys` method of each event handler in the list.
            */
            static void specialKeys(int key, int x, int y) {
                for (auto event : listEvents)
                    event -> specialKeys(key, x, y);
            }
    };

    // Initialize the static list of event pointers
    vector<events*> gameKeyboard::listEvents = vector<events*>();

#endif /* keyboard_hpp */
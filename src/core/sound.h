/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Author: Mateus Silva
 * -----------------------------------------
 */

#pragma once

#ifndef sound_h
    #define sound_h

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
    #include <iostream>

    class Sound 
    {
        public:
            Sound();
            ~Sound();

            void play(const std::string& file);
            void stop();
            void setVolume(int volume);

        private:
            Mix_Music* music;
    };

#endif /* sound_h */
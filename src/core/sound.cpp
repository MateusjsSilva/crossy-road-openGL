/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Author: Mateus Silva
 * -----------------------------------------
 */

#include "sound.h"

Sound::Sound() : music(nullptr) 
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

Sound::~Sound()
{
    if (music) {
        Mix_FreeMusic(music);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void Sound::play(const std::string& file)
{

    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music, -1); // -1 loop 
    }
}

void Sound::stop()
{
    Mix_HaltMusic();
    Mix_CloseAudio();
    SDL_Quit();
}

void Sound::setVolume(int volume)
{
    Mix_VolumeMusic(volume);
}
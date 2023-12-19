/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

    #include <iostream>
    #include <raylib.h>

class SoundWrapper {
    public:
        SoundWrapper(std::string path) {
            sound = LoadMusicStream(path.c_str());
            PlayMusicStream(sound);
        };

        SoundWrapper(std::string path, bool stat) {
            sound = LoadMusicStream(path.c_str());
            PlayMusicStream(sound);
            this->status = stat;
        };

        // ~SoundWrapper() {
        // }

        Music sound;
        bool status = false;
    protected:
    private:
};

#endif /* !SOUND_HPP_ */

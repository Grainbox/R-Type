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
            sound = LoadSound(path.c_str());
        };

        SoundWrapper(std::string path, bool stat) {
            sound = LoadSound(path.c_str());
            this->status = stat;
        };

        ~SoundWrapper() {
            UnloadSound(sound);
        }

        Sound sound;
        bool status = false;
    protected:
    private:
};

#endif /* !SOUND_HPP_ */

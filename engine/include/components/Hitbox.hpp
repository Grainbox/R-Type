/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Hitbox
*/

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

    #include <iostream>

class Hitbox {
    public:
        Hitbox(size_t x, size_t y) : width(x), height(y) {};
        Hitbox(size_t x, size_t y, bool debugs) : width(x), height(y), debug(debugs) {};
        size_t width = 0;
        size_t height = 0;
        bool debug = false;
    protected:
    private:
};

#endif /* !HITBOX_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ReactMouse
*/

#ifndef REACTMOUSE_HPP_
#define REACTMOUSE_HPP_

#include "ECS/Registry.hpp"

class ReactMouse {
    public:
        ReactMouse(const std::function<void(Registry *)>& func) {
            proc = func;
        }
        std::function<void(Registry *)> proc;
    protected:
    private:
};

#endif /* !REACTMOUSE_HPP_ */
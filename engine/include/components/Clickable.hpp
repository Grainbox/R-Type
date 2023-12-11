/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Clickable
*/

#ifndef CLICKABLE_HPP_
#define CLICKABLE_HPP_

#include <SFML/Graphics.hpp>

class Clickable {
    public:
        Clickable(const std::function<void()>& func) {
            proc = func;
        }
        std::function<void()> proc;
    protected:
    private:
};

#endif /* !CLICKABLE_HPP_ */

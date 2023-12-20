/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Clickable
*/

#ifndef CLICKABLE_HPP_
#define CLICKABLE_HPP_

    #include "ECS/Registry.hpp"
    #include <boost/serialization/serialization.hpp>

class Clickable {
    public:
        Clickable(const std::function<void(Registry &, size_t)>& func) {
            proc = func;
        }

        std::function<void(Registry &, size_t)> proc;
    protected:
    private:
};

#endif /* !CLICKABLE_HPP_ */

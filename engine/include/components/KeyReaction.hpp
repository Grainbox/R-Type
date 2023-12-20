/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** KeyReaction
*/

#ifndef KEYREACTION_HPP_
#define KEYREACTION_HPP_

#include "ECS/Registry.hpp"

class KeyReaction {
    public:
        KeyReaction(int key, const std::function<void(Registry &, size_t)>& func) {
            key_value = key;
            proc = func;
        }
        std::function<void(Registry &, size_t)> proc;
        int key_value;
    protected:
    private:
};

#endif /* !KEYREACTION_HPP_ */

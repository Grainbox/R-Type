/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ReactCursor
*/

#ifndef REACTCURSOR_HPP_
#define REACTCURSOR_HPP_

#include "ECS/Registry.hpp"

class ReactCursor {
    public:
        ReactCursor(size_t script_id) : script_id(script_id) {}

        size_t script_id;
    protected:
    private:
};

#endif /* !REACTCURSOR_HPP_ */
/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

// #include "Registry.hpp"

/*!
 \class Position
 \brief Component that is used on entities that has a position.
*/
class Position {
    public:
        Position(float x, float y) : x(x), y(y) {};
        // Position(Entity entity, float x_input, float y_input, Registry &r, std::string scene)
        // {
        //     Position pos(x_input, y_input);
        //     r.addComponent<Position>(entity, pos, scene);
        // };

        float x;
        float y;

    protected:
    private:
};

#endif /* !POSITION_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

/*!
 \class Position
 \brief Component that is used on entities that has a position.
*/
class Position {
    public:
        Position(float x, float y) : x(x), y(y) {};

        float x;
        float y;

    protected:
    private:
};

#endif /* !POSITION_HPP_ */

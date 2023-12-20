/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <boost/serialization/serialization.hpp>

/*!
 \class Position
 \brief Component that is used on entities that has a position.
*/
class Position {
public:
    Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {};

    float x;
    float y;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & x;
        ar & y;
    }

    friend class boost::serialization::access;
protected:
private:
};

#endif /* !POSITION_HPP_ */

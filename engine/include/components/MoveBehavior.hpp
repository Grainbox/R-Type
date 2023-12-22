/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** MoveBehavior
*/

#ifndef MOVEBEHAVIOR_HPP_
#define MOVEBEHAVIOR_HPP_

#include "ECS/Registry.hpp"
#include <boost/serialization/serialization.hpp>

/*!
 \class MoveBehavior
 \brief Component that add rules to entities movements.
*/
class MoveBehavior {
    public:
        MoveBehavior() = default;

        void setOffScreenMov(bool new_value) { _offScreenMov = new_value; };
        bool getOffScreenMov(void) { return _offScreenMov; };

        void setConstMov(int vx, int vy) { constMovX = vx; constMovY = vy; };
        void setConstMovX(int vx) { constMovX = vx; };
        void setConstMovY(int vy) { constMovY = vy; };

        int constMovX;
        int constMovY;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & _offScreenMov;
            ar & constMovX;
            ar & constMovY;
        }

        friend class boost::serialization::access;
    protected:
    private:
        bool _offScreenMov = true;
};

#endif /* !MOVEBEHAVIOR_HPP_ */

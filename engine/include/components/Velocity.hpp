/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

    #include <boost/serialization/serialization.hpp>

/*!
 \class Velocity
 \brief Component that is used on entities that has a velocity.
*/
class Velocity {
    public:
        Velocity(int vx, int vy) : vx(vx), vy(vy) {};

        int vx;
        int vy;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & vx;
            ar & vy;
        }

        friend class boost::serialization::access;

    protected:
    private:
};

#endif /* !VELOCITY_HPP_ */

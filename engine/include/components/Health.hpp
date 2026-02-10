/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Health
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

#include <boost/serialization/serialization.hpp>

/**
 * @struct Health
 * @brief Component for entities with health points.
 */
struct Health {
    Health() = default;
    Health(int hp) : currentHealth(hp), maxHealth(hp) {};

    int currentHealth = 100;
    int maxHealth = 100;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & currentHealth;
        ar & maxHealth;
    }

    friend class boost::serialization::access;
};

#endif /* !HEALTH_HPP_ */

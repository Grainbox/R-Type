/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Boss
*/

#ifndef BOSS_HPP_
#define BOSS_HPP_

#include <boost/serialization/serialization.hpp>

/**
 * @struct Boss
 * @brief Component for boss entities with health segments and phase transitions.
 */
struct Boss {
    Boss() = default;
    Boss(int maxHealth, int segments = 3) 
        : maxHealth(maxHealth), currentHealth(maxHealth), healthSegments(segments), currentPhase(0) {}

    int maxHealth = 300;
    int currentHealth = 300;
    int healthSegments = 3;      // Number of health segments (phases)
    int currentPhase = 0;        // Current phase (0, 1, 2)

    // Calculate which phase we're in based on health
    int calculatePhase() const {
        if (currentHealth <= 0) return healthSegments;
        float healthPercent = static_cast<float>(currentHealth) / maxHealth;
        return healthSegments - static_cast<int>(healthPercent * healthSegments);
    }

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & maxHealth;
        ar & currentHealth;
        ar & healthSegments;
        ar & currentPhase;
    }

    friend class boost::serialization::access;
};

#endif /* !BOSS_HPP_ */

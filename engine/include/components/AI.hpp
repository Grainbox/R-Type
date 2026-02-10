/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** AI
*/

#ifndef AI_HPP_
#define AI_HPP_

#include <boost/serialization/serialization.hpp>

/**
 * @brief Enum representing different AI movement patterns.
 */
enum class AIMode {
    Basic,
    Sinusoidal,
    ZigZag,
    Homing
};

/**
 * @struct AI
 * @brief Component used to define AI behaviors for entities.
 */
struct AI {
    AI() = default;
    AI(AIMode mode, float freq = 1.0f, float amp = 10.0f) : mode(mode), frequency(freq), amplitude(amp) {};

    AIMode mode = AIMode::Basic;
    float timer = 0.0f;           // For time-based patterns
    float frequency = 1.0f;       // Speed of oscillation or direction change
    float amplitude = 10.0f;      // Size of movement
    float startY = 0.0f;          // Reference Y coordinate for patterns
    bool initialized = false;     // Used to capture startY on first update
    size_t targetEntityId = 0;    // Target entity for Homing mode

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & mode;
        ar & timer;
        ar & frequency;
        ar & amplitude;
        ar & startY;
        ar & initialized;
        ar & targetEntityId;
    }

    friend class boost::serialization::access;
};

#endif /* !AI_HPP_ */

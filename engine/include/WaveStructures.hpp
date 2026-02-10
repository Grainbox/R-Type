/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** WaveStructures
*/

#ifndef WAVESTRUCTURES_HPP_
#define WAVESTRUCTURES_HPP_

#include <vector>
#include <string>

enum class EnemyType {
    Sinusoidal,
    ZigZag,
    Homing,
    Boss
};

struct EnemyWaveStep {
    EnemyType type;
    int count;
    float spawnInterval;
    float startX;
    float startY;
    float yRange; // Random Y variation if needed
};

struct EnemyWave {
    std::vector<EnemyWaveStep> steps;
    float timeBeforeNextWave;
};

#endif /* !WAVESTRUCTURES_HPP_ */

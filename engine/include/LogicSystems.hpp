/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** LogicSystems
*/

#ifndef LOGICSYSTEMS_HPP_
#define LOGICSYSTEMS_HPP_

#include "ECS/Registry.hpp"
#include "components/AI.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Boss.hpp"
#include "components/Health.hpp"
#include "components/MoveBehavior.hpp"
#include "WaveStructures.hpp"
#include <cmath>
#include <vector>

namespace Logic {

    inline void update_boss_phases(Registry &r, std::string scene) {
        auto &bosses = r.getComponents<Boss>(scene);
        auto &healths = r.getComponents<Health>(scene);
        auto &ais = r.getComponents<AI>(scene);

        for (size_t i = 0; i < bosses.dense_size(); ++i) {
            Entity boss_id = bosses.get_entity_at(i);
            auto &boss = bosses.dense_at(i);
            auto health = healths[boss_id];
            auto ai = ais[boss_id];

            if (health && ai) {
                boss.currentHealth = health->currentHealth;
                int newPhase = boss.calculatePhase();
                
                if (newPhase != boss.currentPhase && newPhase < boss.healthSegments) {
                    boss.currentPhase = newPhase;
                    if (ai->mode == AIMode::Sinusoidal) {
                        ai->frequency += 0.5f;
                        ai->amplitude += 10.0f;
                    } else if (ai->mode == AIMode::ZigZag) {
                        ai->frequency -= 0.2f;
                        ai->amplitude += 20.0f;
                    }
                }
            }
        }
    }

    inline void update_ai_movement(Registry &r, std::string scene, float dt) {
        auto &ais = r.getComponents<AI>(scene);
        auto &positions = r.getComponents<Position>(scene);
        auto &velocities = r.getComponents<Velocity>(scene);
        auto &moveBehaviors = r.getComponents<MoveBehavior>(scene);

        for (size_t i = 0; i < ais.dense_size(); ++i) {
            Entity entity_id = ais.get_entity_at(i);
            auto &ai = ais.dense_at(i);
            auto pos = positions[entity_id];
            auto vel = velocities[entity_id];

            if (!pos) continue;

            if (!ai.initialized) {
                ai.startY = pos->y;
                ai.initialized = true;
            }

            ai.timer += dt;

            switch (ai.mode) {
                case AIMode::Sinusoidal:
                    pos->y = ai.startY + std::sin(ai.timer * ai.frequency) * ai.amplitude;
                    break;
                case AIMode::ZigZag:
                    if (std::fmod(ai.timer, ai.frequency * 2.0f) < ai.frequency) {
                        if (vel) vel->vy = std::abs(ai.amplitude);
                    } else {
                        if (vel) vel->vy = -std::abs(ai.amplitude);
                    }
                    break;
                case AIMode::Homing:
                    {
                        float nearestDist = std::numeric_limits<float>::max();
                        Position* targetPos = nullptr;

                        for (size_t j = 0; j < moveBehaviors.dense_size(); ++j) {
                            Entity player_id = moveBehaviors.get_entity_at(j);
                            auto &behavior = moveBehaviors.dense_at(j);
                            if (!behavior.isControllable()) continue;
                            auto playerPos = positions[player_id];
                            if (playerPos) {
                                float dx = playerPos->x - pos->x;
                                float dy = playerPos->y - pos->y;
                                float dist = std::sqrt(dx * dx + dy * dy);
                                if (dist < nearestDist) {
                                    nearestDist = dist;
                                    targetPos = &(*playerPos);
                                    ai.targetEntityId = player_id;
                                }
                            }
                        }

                        if (targetPos && vel && nearestDist > 0.1f) {
                            float dx = targetPos->x - pos->x;
                            float dy = targetPos->y - pos->y;
                            float dist = std::sqrt(dx * dx + dy * dy);
                            vel->vx = (dx / dist) * ai.amplitude;
                            vel->vy = (dy / dist) * ai.amplitude;
                        }
                    }
                    break;
                default:
                    break;
            }

            if (vel) {
                // pos->x += vel->vx * dt; // Moved to position_system
                // pos->y += vel->vy * dt;
            }
        }
    }

    inline void position_system(Registry &r, std::string scene, float dt) {
        auto &positions = r.getComponents<Position>(scene);
        auto &velocities = r.getComponents<Velocity>(scene);

        for (size_t i = 0; i < positions.dense_size(); ++i) {
            Entity entity_id = positions.get_entity_at(i);
            auto &pos = positions.dense_at(i);
            auto vel = velocities[entity_id];

            if (vel) {
                pos.x += vel->vx * dt;
                pos.y += vel->vy * dt;

                if (pos.x < -200 || pos.x > 1500) {
                    r.killEntity(entity_id, scene);
                }
            }
        }
    }

    struct WaveState {
        size_t currentWaveIndex = 0;
        size_t currentStepIndex = 0;
        int enemiesSpawnedInStep = 0;
        float spawnTimer = 0.0f;
        float waveTimer = 0.0f;
        bool waveInProgress = false;
    };

    typedef std::function<void(Registry &r, EnemyType type, float x, float y)> SpawnFunc;

    inline void update_waves(Registry &r, std::string scene, float dt, std::vector<EnemyWave> &waves, WaveState &state, SpawnFunc spawnEnemy) {
        if (state.currentWaveIndex >= waves.size()) return;

        EnemyWave &currentWave = waves[state.currentWaveIndex];

        if (state.waveInProgress) {
            auto &ais = r.getComponents<AI>(scene);
            auto &bosses = r.getComponents<Boss>(scene);
            
            if (ais.dense_size() == 0 && bosses.dense_size() == 0 && state.enemiesSpawnedInStep >= currentWave.steps[state.currentStepIndex].count) {
                 state.currentStepIndex++;
                 state.enemiesSpawnedInStep = 0;
                 if (state.currentStepIndex >= currentWave.steps.size()) {
                     state.waveInProgress = false;
                     state.waveTimer = 0.0f;
                 }
            }
        }

        if (!state.waveInProgress) {
            state.waveTimer += dt;
            if (state.waveTimer >= currentWave.timeBeforeNextWave) {
                state.currentWaveIndex++;
                if (state.currentWaveIndex < waves.size()) {
                    state.waveInProgress = true;
                    state.currentStepIndex = 0;
                    state.enemiesSpawnedInStep = 0;
                    state.spawnTimer = 0.0f;
                }
            }
        } else {
            EnemyWaveStep &step = currentWave.steps[state.currentStepIndex];
            if (state.enemiesSpawnedInStep < step.count) {
                state.spawnTimer += dt;
                if (state.spawnTimer >= step.spawnInterval || state.enemiesSpawnedInStep == 0) {
                    float y = step.startY;
                    if (step.yRange > 0) {
                        y += (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f) * step.yRange;
                    }
                    spawnEnemy(r, step.type, step.startX, y);
                    state.enemiesSpawnedInStep++;
                    state.spawnTimer = 0.0f;
                }
            }
        }
    }
}

#endif /* !LOGICSYSTEMS_HPP_ */

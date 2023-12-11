/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(EngineConfig config)
{
    if (!config.isServer) {
        ClientEngine engine(config.r);
    } else {
        ServerEngine engine(config.r, SERVER_PORT);
        engine.run();
    }
}

Engine::~Engine()
{
}

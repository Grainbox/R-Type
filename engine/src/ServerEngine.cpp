/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerEngine
*/

#include "server/ServerEngine.hpp"

ServerEngine::ServerEngine(Registry *r)
{
    this->r = r;
    this->run();
}

void ServerEngine::run()
{
    while (1);
}

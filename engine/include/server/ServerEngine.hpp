/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerEngine
*/

#ifndef SERVERENGINE_HPP_
#define SERVERENGINE_HPP_

#include "ECS/Registry.hpp"
#include "ServerSystem.hpp"
#include <asio.hpp>

class ServerEngine {
    public:
        ServerEngine(Registry *r);

    protected:
    private:
        Registry *r;

        void run();
};

#endif /* !SERVERENGINE_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ClientEngine
*/

#ifndef CLIENTENGINE_HPP_
#define CLIENTENGINE_HPP_

#include "ECS/Registry.hpp"
#include "ClientSystem.hpp"

#include <SFML/Graphics.hpp>

class ClientEngine {
    public:
        ClientEngine(Registry *r);
    protected:
    private:
        sf::RenderWindow window;
        Registry *r;
        ClientSystem system;

        void run();

        void processEvents();

        void update();

        void render();
};

#endif /* !CLIENTENGINE_HPP_ */

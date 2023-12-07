/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics.hpp>

#include "System.hpp"
#include "Registry.hpp"

class Engine {
    public:
        Engine(Registry *r);

        void run();

    protected:
    private:
        sf::RenderWindow window;
        Registry *r;
        System system;

        void processEvents();

        void update();

        void render();

};

#endif /* !ENGINE_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>

#include "components/Controllable.hpp"
#include "components/Drawable.hpp"
#include "components/Velocity.hpp"
#include "components/Position.hpp"

#include "System.hpp"
#include "Registry.hpp"

class Game {
    public:
        Game();

        void run();

    protected:
    private:
        sf::RenderWindow window;
        Registry r;
        System system;

        void initialize();

        void processEvents();

        void update();

        void render();

};

#endif /* !GAME_HPP_ */

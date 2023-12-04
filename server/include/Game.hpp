/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>

#include "Registry.hpp"

class Game {
    public:
        Game() {
            window.create(sf::VideoMode(800, 600), "My Game");

            initialize();
        }

        void run() {
            while (window.isOpen()) {
                processEvents();
                update();
                render();
            }
        }

    protected:
    private:
        sf::RenderWindow window;
        Registry r;

        void initialize() {
            Entity button = this->r.spawnEntity();

            Position pos(100, 0);
            Drawable draw("assets/r-typesheet41.gif");

            this->r.addComponent<Position>(button, pos);
            this->r.addComponent<Drawable>(button, draw);
        }

        void processEvents() {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
        }

        void update() {
            // Mettre à jour la logique de jeu ici
            // Appeler vos systèmes ECS
        }

        void render() {
            window.clear();

            auto position = this->r.getComponents<Position>();
            auto drawable = this->r.getComponents<Drawable>();

            for (size_t i = 0; i < position.size() && i < drawable.size(); ++i)
            {
                auto &pos = position[i].get();
                auto &draw = drawable[i].get();

                draw.sprite.setPosition(pos.x, pos.y);
                window.draw(draw.sprite);
            }

            window.display();
        }

};

#endif /* !GAME_HPP_ */

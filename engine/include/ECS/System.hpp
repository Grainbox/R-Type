/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Registry.hpp"
#include "Sparse_Array.hpp"
#include "components/Controllable.hpp"
#include "components/Drawable.hpp"
#include "components/Velocity.hpp"
#include "components/Position.hpp"

#include <SFML/Graphics.hpp>

class System {
    public:
        void control_system(Registry &r, sf::Event event) {
                std::string scene = r.getCurrentScene();
                Sparse_Array<Controllable> &controllables = r.getComponents<Controllable>(scene);
                Sparse_Array<Velocity> &velocities = r.getComponents<Velocity>(scene);

                for (size_t i = 0; i < controllables.size() && i < velocities.size(); ++i) {
                    auto &vel = velocities[i];

                    if (!vel)
                        continue;

                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Left)
                            vel.value().vx = -1;
                        if (event.key.code == sf::Keyboard::Right)
                            vel.value().vx = 1;
                        if (event.key.code == sf::Keyboard::Up)
                            vel.value().vy = -1;
                        if (event.key.code == sf::Keyboard::Down)
                            vel.value().vy = 1;
                    } else {
                        vel.value().vx = 0;
                        vel.value().vy = 0;
                    }
                }
            }

        void draw_system(Registry &r, sf::RenderWindow &window) {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Position> &positions = r.getComponents<Position>(scene);
            Sparse_Array<Drawable> &drawables = r.getComponents<Drawable>(scene);

            for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
                auto &pos = positions[i];
                auto &draw = drawables[i];

                if (!pos || !draw)
                    continue;

                draw.value().sprite.setTexture(draw.value().texture);
                draw.value().sprite.setPosition(pos.value().x, pos.value().y);

                window.draw(draw.value().sprite);
            }
        }

        void position_system(Registry &r) {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Position> &positions = r.getComponents<Position>(scene);
            Sparse_Array<Velocity> &velocities = r.getComponents<Velocity>(scene);

            for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
                auto &pos = positions[i];
                auto &vel = velocities[i];


                if (!pos || !vel)
                    continue;

                pos.value().x += vel.value().vx;
                pos.value().y += vel.value().vy;
            }
        }
    protected:
    private:

};

#endif /* !SYSTEM_HPP_ */

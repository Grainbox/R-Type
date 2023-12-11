/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** ClientSystem
*/

#ifndef CLIENTSYSTEM_HPP_
#define CLIENTSYSTEM_HPP_

#include "ECS/Registry.hpp"
#include "ECS/Sparse_Array.hpp"
#include "components/Controllable.hpp"
#include "components/Drawable.hpp"
#include "components/Velocity.hpp"
#include "components/Position.hpp"
#include "components/Clickable.hpp"
#include "components/Hitbox.hpp"

#include <SFML/Graphics.hpp>

class ClientSystem {
    public:

        void click_system(Registry &r, sf::Event event, sf::RenderWindow &window) {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Clickable> &clickables = r.getComponents<Clickable>(scene);
            Sparse_Array<Hitbox> &hitboxs = r.getComponents<Hitbox>(scene);
            Sparse_Array<Position> &positions = r.getComponents<Position>(scene);
            for (size_t i = 0; i < clickables.size() && i < hitboxs.size() && i < positions.size(); ++i) {
                auto &click = clickables[i];
                auto &hitbox = hitboxs[i];
                auto &position = positions[i];

                if (!hitbox || !click || !position) continue;
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    if (mouse.x < position.value().x || mouse.x > (position.value().x + hitbox.value().width)) continue;
                    if (mouse.y < position.value().y || mouse.y > (position.value().y + hitbox.value().height)) continue;
                    click.value().proc();
                }
            }
        }

        void control_system(Registry &r, sf::Event event) {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Controllable> &controllables = r.getComponents<Controllable>(scene);
            Sparse_Array<Velocity> &velocities = r.getComponents<Velocity>(scene);

            for (size_t i = 0; i < controllables.size() && i < velocities.size(); ++i) {
                auto &vel = velocities[i];
                auto &controlle = controllables[i];

                if (!vel || !controlle)
                    continue;

                if (event.type == sf::Event::KeyPressed) {
                    if (controlle.value().Left && event.key.code == controlle.value().Left)
                        vel.value().vx = -1;
                    if (controlle.value().Right && event.key.code == controlle.value().Right)
                        vel.value().vx = 1;
                    if (controlle.value().Up && event.key.code == controlle.value().Up)
                        vel.value().vy = -1;
                    if (controlle.value().Down && event.key.code == controlle.value().Down)
                        vel.value().vy = 1;
                } else {
                    vel.value().vx = 0;
                    vel.value().vy = 0;
                }
            }
        }

        void draw_hitbox_system(Registry &r, sf::RenderWindow &window) {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Hitbox> &hitboxs = r.getComponents<Hitbox>(scene);
            Sparse_Array<Position> &positions = r.getComponents<Position>(scene);

            for (size_t i = 0; i < positions.size() && i < hitboxs.size(); ++i) {
                auto &position = positions[i];
                auto &hitbox = hitboxs[i];
                sf::VertexArray LeftLine(sf::Lines, hitbox.value().height);
                sf::VertexArray RightLine(sf::Lines, hitbox.value().height);
                sf::VertexArray TopLine(sf::Lines, hitbox.value().width);
                sf::VertexArray BotLine(sf::Lines, hitbox.value().width);

                if (!hitbox || !position || !hitbox.value().debug) continue;
                for (int i = 0; i < hitbox.value().height; i++) {
                    LeftLine[i].position = sf::Vector2f(position.value().x, position.value().y + i);
                    LeftLine[i].color = sf::Color::Red;
                    RightLine[i].position = sf::Vector2f((position.value().x + hitbox.value().width), position.value().y + i);
                    RightLine[i].color = sf::Color::Red;
                }
                for (int i = 0; i < hitbox.value().width; i++) {
                    TopLine[i].position = sf::Vector2f(position.value().x + i, position.value().y);
                    TopLine[i].color = sf::Color::Red;
                    BotLine[i].position = sf::Vector2f(position.value().x + i, (position.value().y + hitbox.value().height));
                    BotLine[i].color = sf::Color::Red;
                }
                window.draw(LeftLine);
                window.draw(RightLine);
                window.draw(TopLine);
                window.draw(BotLine);
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

#endif /* !CLIENTSYSTEM_HPP_ */

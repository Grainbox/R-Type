/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** System
*/

#include "System.hpp"

void System::control_system(Sparse_Array<Controllable> &controllables,
    Sparse_Array<Velocity> &velocities,
    sf::Event event)
{
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

void System::draw_system(Sparse_Array<Position> &positions,
    Sparse_Array<Drawable> &drawables,
    sf::RenderWindow &window)
{
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

void System::position_system(Sparse_Array<Position> &positions,
    Sparse_Array<Velocity> &velocities)
{
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];


        if (!pos || !vel)
            continue;

        pos.value().x += vel.value().vx;
        pos.value().y += vel.value().vy;
    }
}

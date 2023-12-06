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
        void control_system(Sparse_Array<Controllable> &controllables,
            Sparse_Array<Velocity> &velocities,
            sf::Event event);

        void draw_system(Sparse_Array<Position> &positions,
            Sparse_Array<Drawable> &drawables,
            sf::RenderWindow &window);

        void position_system(Sparse_Array<Position> &positions,
            Sparse_Array<Velocity> &velocities);
    protected:
    private:
};

#endif /* !SYSTEM_HPP_ */

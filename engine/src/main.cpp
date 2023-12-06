/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "Registry.hpp"
#include "Game.hpp"

// void logging_system(Registry *r)
// {
//     auto const &position = r->getComponents<Position>();
//     auto const &velocity = r->getComponents<Velocity>();

//     for (size_t i = 0; i < position.size() && i < velocity.size(); ++i)
//     {
//         auto const &pos = position[i];
//         auto const &vel = velocity[i];

//         std::cout << i << ": Position = { " << pos.get().x << ", " << pos.get().y
//                   << " }, Velocity = { " << vel.get().vx << ", " << vel.get().vy
//                   << " }" << std::endl;
//     }
// }

int main()
{
    try
    {
        Game game;

        game.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

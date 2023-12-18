/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "server/ServerEngine.hpp"

void setupRegistry(Registry &r)
{
    Entity player = r.spawnEntity();

    Position pos(100, 0);
    Controllable control;
    Velocity vel(0, 0);

    r.addComponent<Position>(player, pos, "mainMenu");
    r.addComponent<Controllable>(player, control, "mainMenu");
    r.addComponent<Velocity>(player, vel, "mainMenu");
}

int main()
{
    try
    {
        Registry r("mainMenu");

        setupRegistry(r);

        ServerEngine engine(r, SERVER_PORT);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

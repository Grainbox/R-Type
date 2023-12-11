/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "Engine.hpp"

void setupRegistry(Registry &r)
{
    Entity player = r.spawnEntity();

    Position pos(100, 0);
    Drawable draw("assets/entity_1.png");
    Controllable control;
    Velocity vel(0, 0);

    r.addComponent<Position>(player, pos, "mainMenu");
    r.addComponent<Drawable>(player, draw, "mainMenu");
    r.addComponent<Controllable>(player, control, "mainMenu");
    r.addComponent<Velocity>(player, vel, "mainMenu");

    Entity button = r.spawnEntity();

    Position pos2(200, 200);
    Drawable draw2("assets/entity_2.png");

    r.addComponent<Position>(button, pos2, "mainMenu");
    r.addComponent<Drawable>(button, draw2, "mainMenu");

    Entity player2 = r.spawnEntity();

    r.addComponent<Position>(player2, pos, "game");
    r.addComponent<Drawable>(player2, draw, "game");
    r.addComponent<Controllable>(player2, control, "game");
    r.addComponent<Velocity>(player2, vel, "game");
}

int main()
{
    try
    {
        Registry r("mainMenu");

        setupRegistry(r);

        EngineConfig config = {false, &r};

        Engine engine(config);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

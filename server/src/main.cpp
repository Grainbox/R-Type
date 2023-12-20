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
    Entity player = r.spawnEntity("mainMenu");

    Position pos(100, 0);
    Controllable controls;
    controls.setKeyboardKey(&controls.Up, KEY_UP);
    controls.setKeyboardKey(&controls.Down, KEY_DOWN);
    controls.setKeyboardKey(&controls.Left, KEY_LEFT);
    controls.setKeyboardKey(&controls.Right, KEY_RIGHT);
    Velocity vel(0, 0);
    Drawable draw("assets/entity_1.png", true);

    r.addComponent<Drawable>(player, draw, "mainMenu");
    r.addComponent<Position>(player, pos, "mainMenu");
    r.addComponent<Controllable>(player, controls, "mainMenu");
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

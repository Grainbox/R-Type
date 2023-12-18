/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "client/ClientEngine.hpp"

void debug (Registry &r)
{
    std::cout << "hello world" << std::endl;
}

void setupRegistry(Registry &r)
{
    Entity player = r.spawnEntity();

    Position pos(100, 0);
    Drawable draw("assets/entity_1.png");
    Controllable control;
    Hitbox box(100, 300, true);
    Clickable click(debug);
    Velocity vel(0, 0);

    r.addComponent<Position>(player, pos, "mainMenu");
    r.addComponent<Drawable>(player, draw, "mainMenu");
    r.addComponent<Controllable>(player, control, "mainMenu");
    r.addComponent<Hitbox>(player, box, "mainMenu");
    r.addComponent<Clickable>(player, click, "mainMenu");
    r.addComponent<Velocity>(player, vel, "mainMenu");
}

int main()
{
    try
    {
        Registry r("mainMenu");

        InitWindow(800, 600, "My Engine");
        SetTargetFPS(60);

        setupRegistry(r);

        ClientEngine engine(r, SERVER_PORT);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

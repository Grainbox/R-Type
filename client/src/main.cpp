/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "client/ClientEngine.hpp"

void debug(Registry *r)
{
    // auto inputOpt = r.getEntityComponent<KeyboardInput>(ent, r.getCurrentScene());

    // if (inputOpt.has_value()) {
    //     auto &input = inputOpt.value();
    //     std::cout << input.text << std::endl;
    // } else {
    //     std::cout << "Aucun composant KeyboardInput trouvé pour l'entité." << std::endl;
    // }
}

void setupRegistry(Registry *r)
{
    Entity player = r->spawnEntity();

    Entity playButton = r->spawnEntity();
    Entity settingsButton = r->spawnEntity();
    Entity leaveButton = r->spawnEntity();

    Position pos(300, 100);

    Position playPos(400, 100);
    Position settingsPos(400, 250);
    Position leavePos(400, 400);

    Drawable draw("assets/entity_1.png");
    // Controllable control;
    Hitbox box(100, 100, true);
    Clickable click(debug);
    // Clickable clickPlay(debugClick("playButton"));
    // Velocity vel(0, 0);

    // r->addComponent<Position>(player, pos, "mainMenu");
    // r->addComponent<Drawable>(player, draw, "mainMenu");
    // // r->addComponent<Controllable>(player, control, "mainMenu");
    // r->addComponent<Hitbox>(player, box, "mainMenu");
    // r->addComponent<Clickable>(player, click, "mainMenu");
    // // r->addComponent<Velocity>(player, vel, "mainMenu");

    r->addComponent<Position>(playButton, playPos, "mainMenu");
    r->addComponent<Position>(settingsButton, settingsPos, "mainMenu");
    r->addComponent<Position>(leaveButton, leavePos, "mainMenu");

    r->addComponent<Drawable>(playButton, draw, "mainMenu");
    r->addComponent<Drawable>(settingsButton, draw, "mainMenu");
    r->addComponent<Drawable>(leaveButton, draw, "mainMenu");
}

int main()
{
    try
    {
        Registry r("mainMenu");

        InitWindow(800, 600, "My Engine");
        SetTargetFPS(60);

        setupRegistry(&r);

        ClientEngine engine(&r, SERVER_PORT);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

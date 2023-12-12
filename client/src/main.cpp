/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "client/ClientEngine.hpp"

void debug(Registry &r)
{
    // auto inputOpt = r.getEntityComponent<KeyboardInput>(ent, r.getCurrentScene());

    // if (inputOpt.has_value()) {
    //     auto &input = inputOpt.value();
    //     std::cout << input.text << std::endl;
    // } else {
    //     std::cout << "Aucun composant KeyboardInput trouvé pour l'entité." << std::endl;
    // }
}

void setupRegistry(Registry &r)
{
    Entity textbox = r.spawnEntity();

    std::string message = "";

    Position pos(100, 100);
    Hitbox box(100, 30, true);
    Clickable click(debug);
    KeyboardInput keyboard;

    r.addComponent<Position>(textbox, pos, "mainMenu");
    r.addComponent<Hitbox>(textbox, box, "mainMenu");
    r.addComponent<Clickable>(textbox, click, "mainMenu");
    r.addComponent<KeyboardInput>(textbox, keyboard, "mainMneu");
}

int main()
{
    try
    {
        Registry r("mainMenu");

        setupRegistry(r);

        ClientEngine engine(&r, SERVER_PORT);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

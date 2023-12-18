/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "client/ClientEngine.hpp"
#include "MainView.hpp"

void mainMenu(Registry &r)
{
    MainView mainview(r);
    std::cout << "ici2 " << &r << std::endl;
    mainview.process();
}

void gameScene(Registry &r)
{
    std::string gameScene = "gameScene";
    Entity player = r.spawnEntity();

    Position playerPos(100, 400);
    Drawable drawPlay("assets/entity_1.png");
    Hitbox box(100, 100, true);
    Controllable controls;
    controls.setKeyboardKey(&controls.Up, KEY_Z);
    controls.setKeyboardKey(&controls.Down, KEY_S);
    controls.setKeyboardKey(&controls.Left, KEY_Q);
    controls.setKeyboardKey(&controls.Right, KEY_D);

    r.addComponent<Position>(player, playerPos, gameScene);
    r.addComponent<Drawable>(player, drawPlay, gameScene);
    r.addComponent<Hitbox>(player, box, gameScene);
    r.addComponent<Controllable>(player, controls, gameScene);
}

void setupRegistry(Registry &r)
{
    mainMenu(r);
    gameScene(r);
}

int main()
{
    try
    {
        Registry r("mainMenu");

        int winWidth = 800;
        int winHeigth = 600;

        InitWindow(winWidth, winHeigth, "My Engine");
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

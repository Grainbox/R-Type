/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "client/ClientEngine.hpp"

void pressPlay(Registry *r)
{
    std::cout << "Play button pressed." << std::endl;
}

void pressSettings(Registry *r)
{
    std::cout << "Settings button pressed." << std::endl;
}

void pressExit(Registry *r)
{
    std::cout << "Exit button pressed." << std::endl;
}

void debug(Registry *r)
{
    std::cout << "hello world" << std::endl;
}

void setupRegistry(Registry *r)
{
    // Entity player = r->spawnEntity();

    Entity playButton = r->spawnEntity();
    Entity settingsButton = r->spawnEntity();
    Entity exitButton = r->spawnEntity();

    int ButtonGap = 100;

    int ButtonWidth = GetScreenWidth() / 4;
    int ButtonHeight = GetScreenHeight() / 8;
    int ButtonPosX = (GetScreenWidth() / 2) - (ButtonWidth / 2);
    int ButtonPosY = (GetScreenHeight() / 2) - (ButtonHeight / 2);

    std::cout << "--Button Width: " << ButtonWidth << std::endl;
    std::cout << "--Button posX: " << ButtonPosX << std::endl;


    Position playPos(ButtonPosX, ButtonPosY);
    // Position playPos(100, 100);
    Position settingsPos(ButtonPosX, ButtonPosY + ButtonGap);
    Position leavePos(ButtonPosX, ButtonPosY + (ButtonGap * 2));

    Drawable drawPlay("assets/Play Button.png", ButtonWidth, ButtonHeight);
    Drawable drawSettings("assets/Settings Button.png", ButtonWidth, ButtonHeight);
    Drawable drawLeave("assets/Exit Button.png", ButtonWidth, ButtonHeight);
    // Position pos(300, 100);
    // Controllable control;
    Hitbox box(ButtonWidth, ButtonHeight, true);
    Clickable clickPlay(pressPlay);
    Clickable clickSettings(pressSettings);
    Clickable clickExit(pressExit);
    // Clickable clickPlay(debugClick("playButton"));
    // Velocity vel(0, 0);

    // r->addComponent<Position>(player, pos, "mainMenu");
    // r->addComponent<Drawable>(player, draw, "mainMenu");
    // // r->addComponent<Controllable>(player, control, "mainMenu");
    // r->addComponent<Hitbox>(player, box, "mainMenu");
    // // r->addComponent<Velocity>(player, vel, "mainMenu");

    r->addComponent<Position>(playButton, playPos, "mainMenu");
    r->addComponent<Position>(settingsButton, settingsPos, "mainMenu");
    r->addComponent<Position>(exitButton, leavePos, "mainMenu");

    r->addComponent<Drawable>(playButton, drawPlay, "mainMenu");
    r->addComponent<Drawable>(settingsButton, drawSettings, "mainMenu");
    r->addComponent<Drawable>(exitButton, drawLeave, "mainMenu");

    r->addComponent<Hitbox>(playButton, box, "mainMenu");
    r->addComponent<Hitbox>(settingsButton, box, "mainMenu");
    r->addComponent<Hitbox>(exitButton, box, "mainMenu");

    r->addComponent<Clickable>(playButton, clickPlay, "mainMenu");
    r->addComponent<Clickable>(settingsButton, clickSettings, "mainMenu");
    r->addComponent<Clickable>(exitButton, clickExit, "mainMenu");
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

        setupRegistry(&r);

        ClientEngine engine(&r, SERVER_PORT);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

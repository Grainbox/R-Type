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
#include "GameView.hpp"
#include "ServerGameScene.hpp"

void mainMenu(Registry &r)
{
    MainView mainview(r);
    mainview.process();
}

void gameScene(Registry &r)
{
    GameView gameview(r);
    gameview.process();
}

void setupRegistry(Registry &r)
{
    mainMenu(r);

    ServerGameScene scene(r);
    // gameScene(r);
}

int main()
{
    try
    {
        Registry r("mainMenu");

        int winWidth = 800;
        int winHeigth = 600;
        InitAudioDevice();
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

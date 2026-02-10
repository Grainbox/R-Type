/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "client/ClientEngine.hpp"
#include "RaylibWrapper.hpp"
#include "MainView.hpp"
#include "GameView.hpp"
#include "ServerGameScene.hpp"

void mainMenu(Registry &r, bool isSolo)
{
    MainView mainview(r, isSolo);
    mainview.process();
}

void gameScene(Registry &r)
{
    GameView gameview(r);
    gameview.process();
}

void setupRegistry(Registry &r, bool multiplayer)
{
    mainMenu(r, !multiplayer);

    if (multiplayer)
        ServerGameScene scene(r);
    else
        gameScene(r);
}

int main(int argc, char **argv)
{
    try
    {
        std::string arg;
        Registry r("mainMenu");

        int winWidth = 800;
        int winHeigth = 600;
        InitAudioDevice();
        InitWindow(winWidth, winHeigth, "My Engine");
        ChangeDirectory(GetApplicationDirectory());
        SetTargetFPS(60);

        if (argc == 2)
            arg = argv[1];

        bool isSolo = (arg != "--multiplayer");
        setupRegistry(r, !isSolo);

        ClientEngine engine(r, isSolo, SERVER_PORT);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

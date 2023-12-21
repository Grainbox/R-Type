/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** MainView
*/

#ifndef MAINVIEW_HPP_
#define MAINVIEW_HPP_

    #include "client/ClientEngine.hpp"
    #include "define.hpp"

class MainView {
    public:
        MainView(Registry &r) : r(&r) {};

        void pressPlay(script_settings)
        {
            std::cout << "Play button pressed." << std::endl;

            CreateGameMessage msg;
            msg.header.type = MessageType::Create_Game;

            std::ostringstream archive_stream;
            boost::archive::text_oarchive archive(archive_stream);

            archive << msg;

            std::string serialized_str = archive_stream.str();

            std::cout << "Sending create game" << std::endl;

            _udp_socket.send_to(asio::buffer(serialized_str), _server_endpoint);

            r.setCurrentScene("gameScene");
        }

        void pressSettings(script_settings)
        {
            std::cout << "Settings button pressed." << std::endl;
        }

        void pressExit(script_settings)
        {
            std::cout << "Exit button pressed." << std::endl;
        }

        void reactMPlay(Registry &r)
        {
            // std::cout << "MOUSE DETECTED OVER PLAY BUTTON" << std::endl;

            // Drawable drawPlay("assets/Play col_Button.png", ButtonWidth, ButtonHeight);
            // r->addComponent<Drawable>(playButton, drawPlay, mainMenu);
        }

        void debugPrint(Registry &r)
        {
            std::cout << "key detected" << std::endl;
        }

        void process()
        {
            std::string mainMenu = "mainMenu";

            Entity background = r->spawnEntity(mainMenu);

            Entity playButton = r->spawnEntity(mainMenu);
            Entity settingsButton = r->spawnEntity(mainMenu);
            Entity exitButton = r->spawnEntity(mainMenu);

            int ButtonWidth = GetScreenWidth() / 4;
            int ButtonHeight = GetScreenHeight() / 8;
            int ButtonPosX = (GetScreenWidth() / 2) - (ButtonWidth / 2);
            int ButtonPosY = (GetScreenHeight() / 2) - (ButtonHeight / 2);
            int ButtonGap = 100;

            Position backPos(0, 0);
            Position playPos(ButtonPosX, ButtonPosY);
            Position settingsPos(ButtonPosX, ButtonPosY + ButtonGap);
            Position leavePos(ButtonPosX, ButtonPosY + (ButtonGap * 2));

            Drawable drawBackground("assets/animatedWallpaper.gif", GetScreenWidth(), GetScreenHeight());
            Drawable drawPlay("assets/Play Button.png", ButtonWidth, ButtonHeight);
            Drawable drawSettings("assets/Settings Button.png", ButtonWidth, ButtonHeight);
            Drawable drawLeave("assets/Exit Button.png", ButtonWidth, ButtonHeight);

            Hitbox box(ButtonWidth, ButtonHeight, true);

            Clickable clickPlay(r->registerEventScript(std::bind(
                &MainView::pressPlay, this,
                std::placeholders::_1,
                std::placeholders::_2,
                std::placeholders::_3,
                std::placeholders::_4))
            );

            Clickable clickSettings(r->registerEventScript(std::bind(
                &MainView::pressSettings, this,
                std::placeholders::_1,
                std::placeholders::_2,
                std::placeholders::_3,
                std::placeholders::_4))
            );

            Clickable clickExit(r->registerEventScript(std::bind(
                &MainView::pressExit, this,
                std::placeholders::_1,
                std::placeholders::_2,
                std::placeholders::_3,
                std::placeholders::_4))
            );

            ReactCursor reactPlay(r->registerEventScript(std::bind(
                &MainView::reactMPlay, this,
                std::placeholders::_1))
            );

            r->addComponent<Position>(background, backPos, mainMenu);
            r->addComponent<Position>(playButton, playPos, mainMenu);
            r->addComponent<Position>(settingsButton, settingsPos, mainMenu);
            r->addComponent<Position>(exitButton, leavePos, mainMenu);

            r->addComponent<ReactCursor>(playButton, reactPlay, mainMenu);

            r->addComponent<Drawable>(background, drawBackground, mainMenu);
            r->addComponent<Drawable>(playButton, drawPlay, mainMenu);
            r->addComponent<Drawable>(settingsButton, drawSettings, mainMenu);
            r->addComponent<Drawable>(exitButton, drawLeave, mainMenu);

            r->addComponent<Hitbox>(playButton, box, mainMenu);
            r->addComponent<Hitbox>(settingsButton, box, mainMenu);
            r->addComponent<Hitbox>(exitButton, box, mainMenu);

            r->addComponent<Clickable>(playButton, clickPlay, mainMenu);
            r->addComponent<Clickable>(settingsButton, clickSettings, mainMenu);
            r->addComponent<Clickable>(exitButton, clickExit, mainMenu);

            // KeyReaction Kreact1(KEY_A, std::bind(&MainView::debugPrint, this, std::placeholders::_1));
            // r->addComponent<KeyReaction>(background, Kreact1, mainMenu);
        }
    protected:
    private:
        Registry *r;
};

#endif /* !MAINVIEW_HPP_ */


/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** GameView
*/

#ifndef GAMEVIEW_HPP_
#define GAMEVIEW_HPP_

    #include "client/ClientEngine.hpp"

class GameView {
    public:
        GameView(Registry &r) : r(&r) {};

        void process()
        {
            std::string gameScene = "gameScene";

            Entity player = r->spawnEntity();

            Position playerPos(100, 400);
            Velocity playerVelo(10, 10);
            Drawable drawPlay("assets/entity_1.png");
            Hitbox box(100, 50, true);
            Controllable controls;
            controls.setKeyboardKey(&controls.Up, KEY_UP);
            controls.setKeyboardKey(&controls.Down, KEY_DOWN);
            controls.setKeyboardKey(&controls.Left, KEY_LEFT);
            controls.setKeyboardKey(&controls.Right, KEY_RIGHT);

            AnimatedDraw anim("assets/player.png", 10, 1, 100, 50);

            r->addComponent<Position>(player, playerPos, gameScene);
            r->addComponent<Velocity>(player, playerVelo, gameScene);
            r->addComponent<Drawable>(player, drawPlay, gameScene);
            r->addComponent<Hitbox>(player, box, gameScene);
            r->addComponent<Controllable>(player, controls, gameScene);
            r->addComponent<AnimatedDraw>(player, anim, gameScene);

            Entity ennemy = r->spawnEntity();

            Position ennemyPos(400, 300);
            Velocity ennemyVelo(-1, 0);
            Drawable drawEnnemy("assets/entity_2.png");

            r->addComponent<Position>(ennemy, ennemyPos, gameScene);
            r->addComponent<Velocity>(ennemy, ennemyVelo, gameScene);
            r->addComponent<Drawable>(ennemy, drawEnnemy, gameScene);
            r->addComponent<Hitbox>(ennemy, box, gameScene);

            Entity Title = r->spawnEntity();
            Position titlePos(0, 100);
            Velocity titleVelo(1, 0);
            MoveRight mr;
            Text txt("Hello world", WHITE, 40);
            r->addComponent<Position>(Title, titlePos, gameScene);
            r->addComponent<Velocity>(Title, titleVelo, gameScene);
            r->addComponent<MoveRight>(Title, mr, gameScene);
            r->addComponent<Text>(Title, txt, gameScene);
        }

    protected:
    private:
        Registry *r;
};

#endif /* !GAMEVIEW_HPP_ */

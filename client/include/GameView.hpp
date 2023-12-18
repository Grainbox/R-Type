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
            Drawable drawPlay("assets/entity_1.png");
            Hitbox box(100, 100, true);
            Controllable controls;
            controls.setKeyboardKey(&controls.Up, KEY_Z);
            controls.setKeyboardKey(&controls.Down, KEY_S);
            controls.setKeyboardKey(&controls.Left, KEY_Q);
            controls.setKeyboardKey(&controls.Right, KEY_D);

            r->addComponent<Position>(player, playerPos, gameScene);
            r->addComponent<Drawable>(player, drawPlay, gameScene);
            r->addComponent<Hitbox>(player, box, gameScene);
            r->addComponent<Controllable>(player, controls, gameScene);
        }

    protected:
    private:
        Registry *r;
};

#endif /* !GAMEVIEW_HPP_ */

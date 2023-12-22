/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** GameView
*/

#ifndef GAMEVIEW_HPP_
#define GAMEVIEW_HPP_

    #include "client/ClientEngine.hpp"
    #include "define.hpp"

class GameView {
    public:
        GameView(Registry &r) : r(&r) {};

        void hitTarget(script_settings)
        {
            r.killEntity(entity_id, r.getCurrentScene());
        }

        void shootBullet(Registry &r, size_t entity_id)
        {
            auto shipPosition = r.get_entity_component<Position>(entity_id);
            auto resizeShip = r.get_entity_component<Resize>(entity_id);
            auto hitBoxShip = r.get_entity_component<Hitbox>(entity_id);
            HitTag hitTagShip = hitBoxShip->get().getHitTag();

            if (shipPosition && resizeShip) {
                auto &shipPos = shipPosition->get();
                auto &rsShip = resizeShip->get();
                std::string gameScene = "gameScene";
                Entity bullet = r.spawnEntity(gameScene);
                Resize rsBullet(25, 12);
                Drawable drawBullet("assets/bullet1.png", rsBullet.rx, rsBullet.ry);
                Position posBullet(shipPos.x + rsShip.rx, shipPos.y + (rsShip.ry / 2));
                Velocity velBullet(10, 0);
                Hitbox boxBullet(rsBullet.rx, rsBullet.ry, true);
                boxBullet.setHitTag(hitTagShip);
                OnCollision bulletHit;
                bulletHit.addReaction(HitTag::TAG2, r.registerEventScript(std::bind(&GameView::hitTarget, this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3,
                    std::placeholders::_4)));

                r.addComponent<Position>(bullet, posBullet, gameScene);
                r.addComponent<Resize>(bullet, rsBullet, gameScene);
                r.addComponent<Drawable>(bullet, drawBullet, gameScene);
                r.addComponent<Velocity>(bullet, velBullet, gameScene);
                r.addComponent<Hitbox>(bullet, boxBullet, gameScene);
                r.addComponent<OnCollision>(bullet, bulletHit, gameScene);
            }
        }

        void process()
        {
            std::string gameScene = "gameScene";

            Entity player = r->spawnEntity(gameScene);

            Position playerPos(100, 400);
            Velocity playerVelo(10, 10);
            Drawable drawPlay("assets/entity_1.png");
            Hitbox box(100, 50, true);
            HitTag hTagPlayer(HitTag::TAG1);
            box.setHitTag(hTagPlayer);
            Resize resizePlayer(100, 50);
            Controllable controls;
            controls.setKeyboardKey(&controls.Up, KEY_UP);
            controls.setKeyboardKey(&controls.Down, KEY_DOWN);
            controls.setKeyboardKey(&controls.Left, KEY_LEFT);
            controls.setKeyboardKey(&controls.Right, KEY_RIGHT);
            AnimatedDraw anim("assets/player1.png", 5, 1, resizePlayer.rx, resizePlayer.ry);
            OnCollision shipHit;
            shipHit.addReaction(HitTag::TAG2, r->registerEventScript(std::bind(&GameView::hitTarget, this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3,
                    std::placeholders::_4)));

            r->addComponent<Position>(player, playerPos, gameScene);
            r->addComponent<Velocity>(player, playerVelo, gameScene);
            r->addComponent<Resize>(player, resizePlayer, gameScene);
            r->addComponent<Drawable>(player, drawPlay, gameScene);
            r->addComponent<Hitbox>(player, box, gameScene);
            r->addComponent<Controllable>(player, controls, gameScene);
            r->addComponent<AnimatedDraw>(player, anim, gameScene);
            r->addComponent<OnCollision>(player, shipHit, gameScene);


            Entity ennemy = r->spawnEntity(gameScene);
            Position ennemyPos(400, 300);
            Velocity ennemyVelo(0, 0);
            MoveLeft leftmove;
            Drawable drawEnnemy("assets/entity_2.png");
            Resize resizeEnnemy(100, 100);
            AnimatedDraw anim2("assets/r-typesheet5.gif", 16, 1, resizeEnnemy.rx, resizeEnnemy.ry);

            Hitbox boxEnnemy(100, 50, true);
            HitTag hTagEnnemy(HitTag::TAG2);
            boxEnnemy.setHitTag(hTagEnnemy);
            OnCollision ennemyShipHit;
            ennemyShipHit.addReaction(HitTag::TAG1, r->registerEventScript(std::bind(&GameView::hitTarget, this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3,
                    std::placeholders::_4)));

            r->addComponent<Position>(ennemy, ennemyPos, gameScene);
            r->addComponent<Velocity>(ennemy, ennemyVelo, gameScene);
            r->addComponent<Resize>(ennemy, resizeEnnemy, gameScene);
            r->addComponent<Drawable>(ennemy, drawEnnemy, gameScene);
            r->addComponent<Hitbox>(ennemy, boxEnnemy, gameScene);
            r->addComponent<AnimatedDraw>(ennemy, anim2, gameScene);
            r->addComponent<OnCollision>(ennemy, ennemyShipHit, gameScene);

            // Entity Title = r->spawnEntity(gameScene);
            // Position titlePos(0, 100);
            // Velocity titleVelo(1, 0);
            // MoveRight mr;
            // Text txt("Hello world", WHITE, 40);
            // r->addComponent<Position>(Title, titlePos, gameScene);
            // r->addComponent<Velocity>(Title, titleVelo, gameScene);
            // r->addComponent<MoveRight>(Title, mr, gameScene);
            // r->addComponent<Text>(Title, txt, gameScene);

            KeyReaction Kreact1(KEY_SPACE, std::bind(&GameView::shootBullet, this, std::placeholders::_1, std::placeholders::_2));
            r->addComponent<KeyReaction>(player, Kreact1, gameScene);
        }

    protected:
    private:
        Registry *r;
};

#endif /* !GAMEVIEW_HPP_ */

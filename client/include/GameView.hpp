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
        GameView(Registry &r) : r(r) {};

        bool hitTarget(script_settings)
        {
            r.killEntity(entity_id, r.getCurrentScene());
            return false;
        }

        bool enemyRespawn(script_settings)
        {
            r.killEntity(entity_id, r.getCurrentScene());
            spawn_enemy(r.getCurrentScene(), GetRandomValue(50, 500));
            return false;
        }

        void spawn_enemy(std::string gameScene, int y_pos)
        {
            Entity e1 = r.spawnEntity(gameScene);
            Position pos1(1200, y_pos);
            Velocity vel1(-1, 0);
            Drawable draw1("assets/entity_2.png");
            Resize resize1(60, 60);
            AnimatedDraw anim1("assets/r-typesheet5.gif", 16, 1, resize1.rx, resize1.ry, 0.05f);
            Hitbox box1(100, 50, true);
            HitTag hTag1(HitTag::TAG2);
            box1.setHitTag(hTag1);
            OnCollision hit1;
            hit1.addReaction(HitTag::TAG1, r.registerEventScript(std::bind(&GameView::enemyRespawn, this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3,
                    std::placeholders::_4)));

            r.addComponent<Position>(e1, pos1, gameScene);
            r.addComponent<Velocity>(e1, vel1, gameScene);
            r.addComponent<Resize>(e1, resize1, gameScene);
            r.addComponent<Drawable>(e1, draw1, gameScene);
            r.addComponent<Hitbox>(e1, box1, gameScene);
            r.addComponent<AnimatedDraw>(e1, anim1, gameScene);
            r.addComponent<OnCollision>(e1, hit1, gameScene);
            r.addComponent<AI>(e1, AI(AIMode::Sinusoidal, 2.0f, 50.0f), gameScene);
            r.addComponent<Health>(e1, Health(50), gameScene);
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
                Velocity velBullet(0, 0);
                MoveBehavior movBullet;
                movBullet.setConstMovX(20);
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
                r.addComponent<MoveBehavior>(bullet, movBullet, gameScene);
            }
        }

        void spawn_player(std::string gameScene)
        {
            Entity player = r.spawnEntity(gameScene);

            Position playerPos(100, 400);
            Velocity playerVelo(0, 0);
            Drawable drawPlay("assets/entity_1.png");
            Hitbox box(100, 50, true);
            HitTag hTagPlayer(HitTag::TAG1);
            box.setHitTag(hTagPlayer);
            Resize resizePlayer(100, 50);
            AnimatedDraw anim("assets/player1.png", 5, 1, resizePlayer.rx, resizePlayer.ry, 0.1f);
            OnCollision shipHit;
            shipHit.addReaction(HitTag::TAG2, r.registerEventScript(std::bind(&GameView::hitTarget, this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3,
                    std::placeholders::_4)));
            MoveBehavior shipMovs;
            shipMovs.setOffScreenMov(false);
            shipMovs.setControllable(true);
            shipMovs.addKeyboardKey(shipMovs.UpInput, KEY_UP);
            shipMovs.addKeyboardKey(shipMovs.DownInput, KEY_DOWN);
            shipMovs.addKeyboardKey(shipMovs.LeftInput, KEY_LEFT);
            shipMovs.addKeyboardKey(shipMovs.RightInput, KEY_RIGHT);
            shipMovs.addKeyboardKey(shipMovs.UpInput, KEY_W);
            shipMovs.addKeyboardKey(shipMovs.DownInput, KEY_S);
            shipMovs.addKeyboardKey(shipMovs.LeftInput, KEY_A);
            shipMovs.addKeyboardKey(shipMovs.RightInput, KEY_D);
            KeyReaction Kreact1(KEY_SPACE, std::bind(&GameView::shootBullet, this, std::placeholders::_1, std::placeholders::_2));

            r.addComponent<Position>(player, playerPos, gameScene);
            r.addComponent<Velocity>(player, playerVelo, gameScene);
            r.addComponent<Resize>(player, resizePlayer, gameScene);
            r.addComponent<Drawable>(player, drawPlay, gameScene);
            r.addComponent<Hitbox>(player, box, gameScene);
            // r.addComponent<Controllable>(player, controls, gameScene);
            r.addComponent<AnimatedDraw>(player, anim, gameScene);
            r.addComponent<OnCollision>(player, shipHit, gameScene);
            r.addComponent<MoveBehavior>(player, shipMovs, gameScene);
            r.addComponent<KeyReaction>(player, Kreact1, gameScene);
        }

        void spawn_ai_enemies(std::string gameScene)
        {
            // Sinusoidal Enemy
            Entity e1 = r.spawnEntity(gameScene);
            Position pos1(1100, 150);
            Velocity vel1(-1, 0);
            Drawable draw1("assets/entity_2.png");
            Resize resize1(60, 60);
            AnimatedDraw anim1("assets/r-typesheet5.gif", 16, 1, resize1.rx, resize1.ry, 0.05f);
            Hitbox box1(100, 50, true);
            HitTag hTag1(HitTag::TAG2);
            box1.setHitTag(hTag1);
            OnCollision hit1;
            hit1.addReaction(HitTag::TAG1, r.registerEventScript(std::bind(&GameView::enemyRespawn, this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3,
                    std::placeholders::_4)));

            r.addComponent<Position>(e1, pos1, gameScene);
            r.addComponent<Velocity>(e1, vel1, gameScene);
            r.addComponent<Resize>(e1, resize1, gameScene);
            r.addComponent<Drawable>(e1, draw1, gameScene);
            r.addComponent<Hitbox>(e1, box1, gameScene);
            r.addComponent<AnimatedDraw>(e1, anim1, gameScene);
            r.addComponent<OnCollision>(e1, hit1, gameScene);
            r.addComponent<AI>(e1, AI(AIMode::Sinusoidal, 2.0f, 50.0f), gameScene);
            r.addComponent<Health>(e1, Health(50), gameScene);

            // // ZigZag Enemy
            // Entity e2 = r.spawnEntity(gameScene);
            // Position pos2(1150, 400);
            // Velocity vel2(-70, 50);
            // r.addComponent<Position>(e2, pos2, gameScene);
            // r.addComponent<Velocity>(e2, vel2, gameScene);
            // r.addComponent<Resize>(e2, resize1, gameScene);
            // r.addComponent<Drawable>(e2, draw1, gameScene);
            // r.addComponent<Hitbox>(e2, box1, gameScene);
            // r.addComponent<AnimatedDraw>(e2, anim1, gameScene);
            // r.addComponent<OnCollision>(e2, hit1, gameScene);
            // r.addComponent<AI>(e2, AI(AIMode::ZigZag, 1.5f, 100.0f), gameScene);
            // r.addComponent<Health>(e2, Health(50), gameScene);

            // // Homing Enemy
            // Entity e3 = r.spawnEntity(gameScene);
            // Position pos3(1200, 250);
            // Velocity vel3(0, 0);
            // r.addComponent<Position>(e3, pos3, gameScene);
            // r.addComponent<Velocity>(e3, vel3, gameScene);
            // r.addComponent<Resize>(e3, resize1, gameScene);
            // r.addComponent<Drawable>(e3, draw1, gameScene);
            // r.addComponent<Hitbox>(e3, box1, gameScene);
            // r.addComponent<AnimatedDraw>(e3, anim1, gameScene);
            // r.addComponent<OnCollision>(e3, hit1, gameScene);
            // r.addComponent<AI>(e3, AI(AIMode::Homing, 1.0f, 80.0f), gameScene);
            // r.addComponent<Health>(e3, Health(75), gameScene);
        }

        void spawn_boss(std::string gameScene)
        {
            Entity boss = r.spawnEntity(gameScene);
            Position bossPos(700, 300);
            Velocity bossVel(-50, 0);
            Drawable bossDraw("assets/entity_2.png");
            Resize bossResize(150, 150);
            AnimatedDraw bossAnim("assets/r-typesheet5.gif", 16, 1, bossResize.rx, bossResize.ry, 0.05f);
            Hitbox bossBox(150, 100, true);
            HitTag bossTag(HitTag::TAG2);
            bossBox.setHitTag(bossTag);
            OnCollision bossHit;
            bossHit.addReaction(HitTag::TAG1, r.registerEventScript(std::bind(&GameView::enemyRespawn, this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3,
                    std::placeholders::_4)));

            r.addComponent<Position>(boss, bossPos, gameScene);
            r.addComponent<Velocity>(boss, bossVel, gameScene);
            r.addComponent<Resize>(boss, bossResize, gameScene);
            r.addComponent<Drawable>(boss, bossDraw, gameScene);
            r.addComponent<Hitbox>(boss, bossBox, gameScene);
            r.addComponent<AnimatedDraw>(boss, bossAnim, gameScene);
            r.addComponent<OnCollision>(boss, bossHit, gameScene);
            r.addComponent<AI>(boss, AI(AIMode::Sinusoidal, 1.0f, 30.0f), gameScene);
            r.addComponent<Health>(boss, Health(300), gameScene);
            r.addComponent<Boss>(boss, Boss(300, 3), gameScene);
        }

        void process()
        {
            std::string gameScene = "gameScene";
            spawn_player(gameScene);
            spawn_ai_enemies(gameScene);
            // spawn_boss(gameScene);
        }

    protected:
    private:
        Registry &r;
};

#endif /* !GAMEVIEW_HPP_ */

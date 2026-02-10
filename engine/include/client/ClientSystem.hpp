/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** ClientSystem
*/

/**
 * @file ClientSystem.hpp
 * @brief Contient la déclaration de la classe ClientSystem.
 *
 * Ce fichier décrit les interfaces et les interactions des systèmes clients
 * utilisés dans le projet B-CPP-500-REN-5-2-bsrtype-tom.daniel.
 */

#ifndef CLIENTSYSTEM_HPP_
#define CLIENTSYSTEM_HPP_

#include "RaylibWrapper.hpp"
#include <asio.hpp>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "ECS/Registry.hpp"
#include "ECS/Sparse_Array.hpp"
#include <optional>
#include "Communication_Structures.hpp"
#include "ResourceManager.hpp"

/**
 * @class ClientSystem
 * @brief Gère les interactions client dans le jeu.
 *
 * La classe ClientSystem offre plusieurs systèmes pour gérer les interactions
 * client, comme la gestion des clics, le contrôle des entités, l'affichage
 * et la mise à jour des positions.
 */
class ClientSystem {
    public:
        ClientSystem(Registry &r, short server_port) : _udp_socket(io_context), r(r),
            _server_endpoint(asio::ip::udp::endpoint(asio::ip::address::from_string("127.0.0.1"), server_port))
        {
            _udp_socket.open(asio::ip::udp::v4());

            start_receive();
        }

        ~ClientSystem()
        {
            ResourceManager::getInstance().clear();
        }

        void send_disconnect()
        {
            DisconnectMessage msg;

            msg.header.type = MessageType::Disconnect;
            msg.reason = "Client Input";

            std::ostringstream archive_stream;
            boost::archive::text_oarchive archive(archive_stream);

            archive << msg;

            std::string serialized_str = archive_stream.str();

            std::cout << "Sending Disconnect" << std::endl;

            _udp_socket.send_to(asio::buffer(serialized_str), _server_endpoint);
        }

        /*!
        \brief Send the first connection message to the server
        */
        void send_first_con()
        {
            FirstConMessage msg;
            msg.header.type = MessageType::First_Con;

            std::ostringstream archive_stream;
            boost::archive::text_oarchive archive(archive_stream);

            archive << msg;

            std::string serialized_str = archive_stream.str();

            std::cout << "Sending First Con" << std::endl;

            _udp_socket.send_to(asio::buffer(serialized_str), _server_endpoint);
        }

        /*!
        \brief Listen for the server messages asynchronously.
        */
        void start_receive()
        {
            _udp_socket.async_receive_from(
                asio::buffer(recv_buffer_), _server_endpoint,
                [this](std::error_code ec, std::size_t bytes_recvd)
                {
                    handle_receive_system(ec, bytes_recvd);
                });
        }

        /*!
        \brief Handles data received from the server.

        \param error Boost ASIO error code, if any.
        \param bytes_transferred Number of bytes received.
        */
        void handle_receive_system(const std::error_code &error, std::size_t bytes_transferred)
        {
            if (!error)
            {
                std::cout << "-------------------------------------" << std::endl;
                std::string received_message(recv_buffer_, bytes_transferred);
                std::cout << "Received: " << received_message << std::endl;

                std::istringstream archive_stream(received_message);
                boost::archive::text_iarchive archive(archive_stream);
                FirstConMessage msg;
                archive >> msg;

                std::string returnMessage = "ERROR";

                std::cout << "Deserialized message type: " << static_cast<int>(msg.header.type) << std::endl << std::endl;

                std::string scene = r.getCurrentScene();
                Sparse_Array<ReceiveUDP> &udpComp = r.getComponents<ReceiveUDP>(scene);

                for (size_t i = 0; i < udpComp.dense_size(); i++) {
                    size_t entity_id = udpComp.get_entity_at(i);
                    auto &udp = udpComp.dense_at(i);

                    MessageHandlerData data = {received_message, msg.header.type, _udp_socket, _server_endpoint, clients_entity, client_server_entity_id, localEndpoint};
                    r.getComScript(udp.script_id)(r, entity_id, data);
                }

                std::cout << "-------------------------------------" << std::endl;
            } else {
                std::cout << "Error: " << error << std::endl;
            }
            start_receive();
        }

        void Health_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Health> &life = r.getComponents<Health>(scene);

            for (size_t i = 0; i < life.dense_size(); ++i) {
                auto &pv = life.dense_at(i);
                if (!pv.currentHealth)
                    r.remove_component<Health>(life.get_entity_at(i), scene);
            }
        }

        void SoundWrapper_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<SoundWrapper> &soundbox = r.getComponents<SoundWrapper>(scene);

            for (size_t i = 0; i < soundbox.size(); ++i) {
                auto sound = soundbox[i];

                if (!sound && sound.value().status) continue;
                UpdateMusicStream(sound.value().sound);
            }
        }
        /**
         * @brief Analyse les données du composant MoveBehavior et met à jour la
         * velocité en conséquence.
         */
        void Move_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Velocity> &velocity = r.getComponents<Velocity>(scene);
            Sparse_Array<Position> &position = r.getComponents<Position>(scene);
            Sparse_Array<MoveBehavior> &behaviors = r.getComponents<MoveBehavior>(scene);

            for (size_t i = 0; i < behaviors.dense_size(); ++i) {
                size_t entity_id = behaviors.get_entity_at(i);
                auto &behavior = behaviors.dense_at(i);
                auto vel = velocity[entity_id];
                auto pos = position[entity_id];

                if (!vel || !pos)
                    continue;

                // Réinitialisation de la vélocité de l'entité.
                vel->vx = 0;
                vel->vy = 0;

                int move_speed = 1;
                if (behavior.getMoveSpeed() != 0)
                    move_speed = behavior.getMoveSpeed();

                // Process d'ajout des mouvements constants enregistrés.
                if (behavior.constMovX)
                    vel->vx += behavior.constMovX * move_speed;
                if (behavior.constMovY)
                    vel->vy += behavior.constMovY * move_speed;

                // Process de mis à jour de la vélocité selon les controls
                if (behavior.isControllable()) {
                    if (behavior.PressUp)
                        vel->vy -= move_speed;
                    if (behavior.PressDown)
                        vel->vy += move_speed;
                    if (behavior.PressLeft)
                        vel->vx -= move_speed;
                    if (behavior.PressRight)
                        vel->vx += move_speed;
                }

                // process empêchant l'entité de sortir de l'écran.
                if (behavior.getOffScreenMov() == false) {
                    if ((vel->vx < 0 && pos->x <= 0) ||
                        (vel->vx > 0 && pos->x >= GetScreenWidth()))
                        vel->vx = 0;
                    if ((vel->vy < 0 && pos->y <= 0) ||
                        (vel->vy > 0 && pos->y >= GetScreenHeight()))
                        vel->vy = 0;
                }
            }
        }

        void control_system_tmp() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Controllable> &controllables = r.getComponents<Controllable>(scene);
            Sparse_Array<Velocity> &velocities = r.getComponents<Velocity>(scene);

            for (size_t i = 0; i < controllables.dense_size(); ++i) {
                size_t entity_id = controllables.get_entity_at(i);
                auto &control = controllables.dense_at(i);
                auto vel = velocities[entity_id];

                if (!vel)
                    continue;

                // Réinitialiser la vitesse
                vel->vx = 0;
                vel->vy = 0;

                // Vérifier les touches pressées et ajuster la vitesse en conséquence
                for (int key : control.Left)
                    if (IsKeyDown(key)) vel->vx = -1;
                for (int key : control.Right)
                    if (IsKeyDown(key)) vel->vx = 1;
                for (int key : control.Up)
                    if (IsKeyDown(key)) vel->vy = -1;
                for (int key : control.Down)
                    if (IsKeyDown(key)) vel->vy = 1;
            }
        }

        /**
         * @brief Détecte les appuies des touches pour le controle des entités
         * controllables.
         *
         * Ce système parcourt toutes les entités disposant de composants
         * 'MoveBehavior' avec l'option 'Controllable' et vérifie si les touches
         * paramétrées pour le controle de l'entité son appuyées.
         */
        void control_system()
        {
            control_system_tmp();
            std::string scene = r.getCurrentScene();
            Sparse_Array<MoveBehavior> &behaviors = r.getComponents<MoveBehavior>(scene);

            for (size_t i = 0; i < behaviors.dense_size(); ++i) {
                auto &behavior = behaviors.dense_at(i);

                // Réinitialisation des booléen attestant l'appuie des touches.
                behavior.PressUp = false;
                behavior.PressDown = false;
                behavior.PressLeft = false;
                behavior.PressRight = false;

                // Récupération de l'info via la fonction raylib 'isKeyDown'
                for (int key : behavior.UpInput)
                    if (IsKeyDown(key)) behavior.PressUp = true;
                for (int key : behavior.DownInput)
                    if (IsKeyDown(key)) behavior.PressDown = true;
                for (int key : behavior.LeftInput)
                    if (IsKeyDown(key)) behavior.PressLeft = true;
                for (int key : behavior.RightInput)
                    if (IsKeyDown(key)) behavior.PressRight = true;
            }
        }

        void Text_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Text> &txt = r.getComponents<Text>(scene);
            Sparse_Array<Position> &position = r.getComponents<Position>(scene);

            for (size_t i = 0; i < txt.dense_size(); ++i) {
                size_t entity_id = txt.get_entity_at(i);
                auto &text = txt.dense_at(i);
                auto pos = position[entity_id];

                if (!pos) continue;

                DrawText(TextFormat(text.text.c_str()), pos->x, pos->y, text.font_size, text.rgb);
            }
        }

        /**
         * @brief Gère les touches du clavier appuyées par l'utilisateur.
         *
         * Ce système détecte touches du clavier et déclenche des actions.
         *
         * @param r Référence à l'objet Registry contenant les entités et composants.
         */
        void key_detection_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<KeyReaction> &KReactions = r.getComponents<KeyReaction>(scene);

            for (size_t i = 0; i < KReactions.size(); ++i) {
                auto KReact = KReactions[i];

                if (!KReact)
                    continue;

                if (IsKeyPressed(KReact.value().key_value))
                    KReact.value().proc(r, i);
            }
        }

        /**
         * @brief Gère les clics de l'utilisateur.
         *
         * Ce système détecte les clics de souris et déclenche des actions
         * si un objet cliquable est touché.
         *
         * @param r Référence à l'objet Registry contenant les entités et composants.
         * @param event Événement SFML capturé.
         * @param window Fenêtre SFML pour la capture de la position de la souris.
         */
        void click_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Clickable> &clickables = r.getComponents<Clickable>(scene);
            Sparse_Array<Hitbox> &hitboxs = r.getComponents<Hitbox>(scene);
            Sparse_Array<Position> &positions = r.getComponents<Position>(scene);

            for (size_t i = 0; i < clickables.size() && i < hitboxs.size() && i < positions.size(); ++i) {
                auto click = clickables[i];
                auto hitbox = hitboxs[i];
                auto position = positions[i];

                if (!hitbox || !click || !position)
                    continue;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mouse = GetMousePosition();
                    if (mouse.x < position.value().x || mouse.x > (position.value().x + hitbox.value().width)) continue;
                    if (mouse.y < position.value().y || mouse.y > (position.value().y + hitbox.value().height)) continue;
                    if (!r.getEventScript(click.value().script_id)(r, i, _udp_socket, _server_endpoint)) continue;
                }
            }
        }

        /**
         * @brief Gère le passage de la sourie de l'utilisateur.
         *
         * Ce système détecte la souris et déclenche des actions si un objet
         * réagissant est en contact avec la souris (sans click).
         *
         * @param r Référence à l'objet Registry contenant les entités et composants.
         * @param event Événement SFML capturé.
         * @param window Fenêtre SFML pour la capture de la position de la souris.
         */
        void reactCursor_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<ReactCursor> &reactCursors = r.getComponents<ReactCursor>(scene);
            Sparse_Array<Hitbox> &hitboxs = r.getComponents<Hitbox>(scene);
            Sparse_Array<Position> &positions = r.getComponents<Position>(scene);

            for (size_t i = 0; i < reactCursors.size() && i < hitboxs.size() && i < positions.size(); ++i) {
                auto reactC = reactCursors[i];
                auto hitbox = hitboxs[i];
                auto position = positions[i];

                if (!hitbox || !reactC || !position)
                    continue;

                Vector2 mouse = GetMousePosition();
                if (mouse.x < position.value().x || mouse.x > (position.value().x + hitbox.value().width)) continue;
                if (mouse.y < position.value().y || mouse.y > (position.value().y + hitbox.value().height)) continue;
                r.getEventScript(reactC.value().script_id);
            }
        }
        /**
         * @brief Détecte les collisions entre entités avec hitbox.
         *
         * Ce système parcourt toutes les entités disposant de composants `Hitbox`
         * et "Position", puis liste les entités avec lesquelles une collision
         * a lieu.
         */
        void hitbox_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Hitbox> &hitboxs = r.getComponents<Hitbox>(scene);
            Sparse_Array<Position> &positions = r.getComponents<Position>(scene);

            for (size_t i = 0; i < hitboxs.dense_size(); ++i) {
                size_t id = hitboxs.get_entity_at(i);
                auto hitbox = hitboxs.dense_at(i);
                auto pos = positions[id];

                if (!pos) continue;

                hitbox.clearCollisionList();

                int leftX = pos->x;
                int rightX = pos->x + hitbox.width;
                int topY = pos->y;
                int bottomY = pos->y + hitbox.height;

                for (size_t j = 0; j < hitboxs.dense_size(); ++j) {
                    if (i == j) continue;
                    size_t id_other = hitboxs.get_entity_at(j);
                    auto &hitbox2 = hitboxs.dense_at(j);
                    auto pos2 = positions[id_other];

                    if (!pos2) continue;

                    int leftX2 = pos2->x;
                    int rightX2 = pos2->x + hitbox2.width;
                    int topY2 = pos2->y;
                    int bottomY2 = pos2->y + hitbox2.height;

                    if (((leftX >= leftX2 && leftX <= rightX2) || (rightX >= leftX2 && rightX <= rightX2)) &&
                        ((topY >= topY2 && topY <= bottomY2) || (bottomY >= topY2 && bottomY <= bottomY2))) {
                        hitbox.enterCollision(id_other, hitbox2.getHitTag().tag);
                        std::cout << "collision " << id_other << " entered in " << id << std::endl;
                    }
                }
            }
        }

        /**
         * @brief Execute les réactions aux collisions.
         *
         * Ce système parcourt toutes les entités disposant de composants `Hitbox`
         * et "OnCollision", puis execute les réactions listé lorsque leur tag
         * de collision est présent dans la liste des collisions de l'entité.
         */
        void collision_reaction_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<OnCollision> &onCols = r.getComponents<OnCollision>(scene);
            Sparse_Array<Hitbox> &hitboxs = r.getComponents<Hitbox>(scene);
            bool entityAlive = true;

            for (size_t i = 0; i < onCols.dense_size(); ++i) {
                size_t entity_id = onCols.get_entity_at(i);
                auto &collision = onCols.dense_at(i);
                auto hitbox = hitboxs[entity_id];

                if (!hitbox || hitbox->getCollisionList().empty())
                    continue;
                for (auto reaction : collision.reactionsList) {
                    HitTag::hitTag tag = reaction.first;
                    size_t script_id = reaction.second;
                    for (auto collisionInfo : hitbox->getCollisionList()) {
                        if (collisionInfo.second == tag) {
                            entityAlive = r.getEventScript(script_id)(r, entity_id, _udp_socket, _server_endpoint);
                            if (!entityAlive)
                                break;
                        }
                    }
                    if (!entityAlive)
                        break;
                }
            }
        }
        /**
         * @brief Dessine les hitbox à l'écran.
         *
         * Ce système parcourt toutes les entités disposant de composants `Hitbox`
         * et "Position", puis dessine les hitbox à l'écran (system de debug).
         */
        void draw_hitbox_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Hitbox> &hitboxs = r.getComponents<Hitbox>(scene);
            Sparse_Array<Position> &positions = r.getComponents<Position>(scene);

            for (size_t i = 0; i < positions.size() && i < hitboxs.size(); ++i) {
                auto position = positions[i];
                auto hitbox = hitboxs[i];

                if (!hitbox || !position || !hitbox.value().debug)
                    continue;

                // Dessiner le contour de la hitbox
                int leftX = position.value().x;
                int rightX = position.value().x + hitbox.value().width;
                int topY = position.value().y;
                int bottomY = position.value().y + hitbox.value().height;

                Color hitboxColor = WHITE;
                if (hitbox.value().getHitTag().tag == HitTag::TAG1)
                    hitboxColor = BLUE;
                else if (hitbox.value().getHitTag().tag == HitTag::TAG2)
                    hitboxColor = RED;

                // Lignes verticales
                DrawLine(leftX, topY, leftX, bottomY, hitboxColor);
                DrawLine(rightX, topY, rightX, bottomY, hitboxColor);

                // Lignes horizontales
                DrawLine(leftX, topY, rightX, topY, hitboxColor);
                DrawLine(leftX, bottomY, rightX, bottomY, hitboxColor);
            }
        }
        /**
         * @brief Met à jour la texture selon un spritesheet.
         *
         * Ce système parcourt toutes les entités disposant de composants `AnimatedDraw`
         * et "Drawable" et mets à jour Drawable à partir du "AnimatedDraw".
         */
        void update_sprites_system() {
            std::string scene = r.getCurrentScene();
            auto &drawables = r.getComponents<Drawable>(scene);
            auto &animations = r.getComponents<AnimatedDraw>(scene);
            float dt = GetFrameTime();

            for (size_t i = 0; i < animations.dense_size(); ++i) {
                size_t entity_id = animations.get_entity_at(i);
                auto &anim = animations.dense_at(i);
                auto draw = drawables[entity_id];

                if (draw) {
                    anim.timeAccumulator += dt;
                    if (anim.timeAccumulator >= anim._frameDuration) {
                        anim.timeAccumulator -= anim._frameDuration;
                        anim.currentFrame++;
                        if (anim.currentFrame >= anim._nbCols) {
                            if (anim._loop)
                                anim.currentFrame = 0;
                            else
                                anim.currentFrame = anim._nbCols - 1;
                        }
                        draw->texture = anim.textureList.at(anim.currentRow).at(anim.currentFrame);
                    }
                }
            }
        }

        /**
         * @brief Dessine les entités sur la fenêtre de rendu.
         *
         * Ce système parcourt toutes les entités disposant de composants `Drawable`
         * et `Position` et les dessine dans la fenêtre SFML.
         *
         * @param r Référence à l'objet Registry contenant les entités et composants.
         * @param window Fenêtre SFML dans laquelle les entités sont dessinées.
         */
        void draw_system() {
            std::string scene = r.getCurrentScene();
            auto &positions = r.getComponents<Position>(scene);
            auto &drawables = r.getComponents<Drawable>(scene);

            for (size_t i = 0; i < drawables.dense_size(); ++i) {
                size_t entity_id = drawables.get_entity_at(i);
                auto &draw = drawables.dense_at(i);
                auto pos = positions[entity_id];

                if (pos) {
                    Vector2 position = { pos->x, pos->y };
                    DrawTextureV(draw.texture, position, WHITE);
                }
            }
        }

        /**
         * @brief Met à jour la position des entités en fonction de leur vitesse.
         *
         * Ce système met à jour la position des entités qui ont des composantes
         * `Position` et `Velocity` en fonction de leur vitesse actuelle.
         */
        void position_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Position> &positions = r.getComponents<Position>(scene);
            Sparse_Array<Velocity> &velocities = r.getComponents<Velocity>(scene);

            for (size_t i = 0; i < velocities.dense_size(); ++i) {
                size_t entity_id = velocities.get_entity_at(i);
                auto &vel = velocities.dense_at(i);
                auto pos = positions[entity_id];

                if (!pos || (vel.vx == 0 && vel.vy == 0))
                    continue;

                pos->x += vel.vx;
                pos->y += vel.vy;

                TransfertECSMessage msg;
                msg.header.type = MessageType::ECS_Transfert;

                EntityComponents comps;

                auto server_id = findKeyByValue(client_server_entity_id, i);

                if (!server_id)
                    continue;

                comps.entity_id = server_id.value();
                comps.scene = r.getCurrentScene();

                comps.position = r.get_boost_entity_component<Position>(i);

                msg.entities.push_back(comps);

                std::ostringstream archive_stream;
                boost::archive::text_oarchive archive(archive_stream);
                archive << msg;

                std::string serialized_str = archive_stream.str();

                _udp_socket.async_send_to(
                    asio::buffer(serialized_str), _server_endpoint,
                    [](const std::error_code& error, std::size_t bytes_transferred) {
                        if (!error) {
                            std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
                        } else {
                            std::cerr << "Error sending message: " << error.message() << std::endl;
                        }
                    }
                );
            }
        }

        asio::io_context io_context;
    protected:
    private:
        std::optional<size_t> findKeyByValue(
            const std::unordered_map<size_t, size_t> &client_server_entity_id,
            size_t value) {
            for (const auto &pair : client_server_entity_id) {
                if (pair.second == value) {
                    return pair.first; // Retourne la clé si la valeur correspond
                }
            }

            return {}; // Retourne std::nullopt si aucune correspondance n'est trouvée
        }

        std::unordered_map<std::string, size_t> clients_entity;
        std::unordered_map<size_t, size_t> client_server_entity_id;

        asio::ip::udp::socket _udp_socket;
        asio::ip::udp::endpoint _server_endpoint;
        char recv_buffer_[1024];

        std::string localEndpoint;

        Registry &r;

};

#endif /* !CLIENTSYSTEM_HPP_ */

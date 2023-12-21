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

#include "ECS/Registry.hpp"
#include "ECS/Sparse_Array.hpp"
#include "Communication_Structures.hpp"

#include <asio.hpp>
#include <raylib.h>

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
        ClientSystem(Registry &r, short server_port) : _udp_socket(io_context), r(r)
        {
            _udp_socket.open(asio::ip::udp::v4());
            _server_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string("127.0.0.1"), server_port);

            start_receive();
        }

        ~ClientSystem()
        {
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

                for (size_t i = 0; i < udpComp.size(); i++) {
                    auto &udp = udpComp[i];

                    if (!udp)
                        continue;

                    returnMessage = r.getComScript(udp.value().script_id)(r, i, received_message, msg.header.type);
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

            for (size_t i = 0; i < life.size(); ++i) {
                auto &pv = life[i];

                if (!pv) continue;
                if (!pv.value().health)
                    r.remove_component<Health>(i, scene);
            }
        }

        void SoundWrapper_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<SoundWrapper> &soundbox = r.getComponents<SoundWrapper>(scene);

            for (size_t i = 0; i < soundbox.size(); ++i) {
                auto &sound = soundbox[i];

                if (!sound && sound.value().status) continue;
                UpdateMusicStream(sound.value().sound);
            }
        }

        void Move_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<MoveLeft> &moveLeft = r.getComponents<MoveLeft>(scene);
            Sparse_Array<MoveRight> &moveRight = r.getComponents<MoveRight>(scene);
            Sparse_Array<MoveUp> &moveUp = r.getComponents<MoveUp>(scene);
            Sparse_Array<MoveDown> &moveDown = r.getComponents<MoveDown>(scene);
            Sparse_Array<Velocity> &velocity = r.getComponents<Velocity>(scene);
            Sparse_Array<Position> &position = r.getComponents<Position>(scene);

            for (size_t i = 0; i < moveLeft.size() && i < moveRight.size() && i < moveDown.size() && i < moveUp.size() && i < velocity.size() && i < position.size(); ++i) {
                auto &left = moveLeft[i];
                auto &right = moveRight[i];
                auto &up = moveUp[i];
                auto &down = moveDown[i];
                auto &mov = velocity[i];
                auto &pos = position[i];

                if (!mov || !pos) continue;

                if (left)
                    mov.value().vx += -1;
                if (right)
                    mov.value().vx += 1;
                if (up)
                    mov.value().vy += -1;
                if (down)
                    mov.value().vy += 1;
                continue;
            }
        }

        void Text_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Text> &txt = r.getComponents<Text>(scene);
            Sparse_Array<Position> &position = r.getComponents<Position>(scene);

            for (size_t i = 0; i < txt.size() && i < position.size(); ++i) {
                auto &text = txt[i];
                auto &pos = position[i];

                if (!text || !pos) continue;

                DrawText(TextFormat(text.value().text.c_str()), pos.value().x, pos.value().y, text.value().font_size, text.value().rgb);
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
                auto &KReact = KReactions[i];

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
                auto &click = clickables[i];
                auto &hitbox = hitboxs[i];
                auto &position = positions[i];

                if (!hitbox || !click || !position)
                    continue;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mouse = GetMousePosition();
                    if (mouse.x < position.value().x || mouse.x > (position.value().x + hitbox.value().width)) continue;
                    if (mouse.y < position.value().y || mouse.y > (position.value().y + hitbox.value().height)) continue;
                    r.getEventScript(click.value().script_id)(r, i, _udp_socket, _server_endpoint);
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
                auto &reactM = reactCursors[i];
                auto &hitbox = hitboxs[i];
                auto &position = positions[i];

                if (!hitbox || !reactM || !position)
                    continue;

                Vector2 mouse = GetMousePosition();
                if (mouse.x < position.value().x || mouse.x > (position.value().x + hitbox.value().width)) continue;
                if (mouse.y < position.value().y || mouse.y > (position.value().y + hitbox.value().height)) continue;
                r.getEventScript(reactM.value().script_id);
            }
        }

        void control_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Controllable> &controllables = r.getComponents<Controllable>(scene);
            Sparse_Array<Velocity> &velocities = r.getComponents<Velocity>(scene);

            for (size_t i = 0; i < controllables.size() && i < velocities.size(); ++i) {
                auto &vel = velocities[i];
                auto &controlle = controllables[i];

                if (!vel || !controlle)
                    continue;

                // Réinitialiser la vitesse
                vel.value().vx = 0;
                vel.value().vy = 0;

                // Vérifier les touches pressées et ajuster la vitesse en conséquence
                if (controlle.value().Left != -1 && IsKeyDown(controlle.value().Left))
                    vel.value().vx = -1;
                if (controlle.value().Right != -1 && IsKeyDown(controlle.value().Right))
                    vel.value().vx = 1;
                if (controlle.value().Up != -1 && IsKeyDown(controlle.value().Up))
                    vel.value().vy = -1;
                if (controlle.value().Down != -1 && IsKeyDown(controlle.value().Down))
                    vel.value().vy = 1;
            }
        }

        void draw_hitbox_system() {
            std::string scene = r.getCurrentScene();
            Sparse_Array<Hitbox> &hitboxs = r.getComponents<Hitbox>(scene);
            Sparse_Array<Position> &positions = r.getComponents<Position>(scene);

            for (size_t i = 0; i < positions.size() && i < hitboxs.size(); ++i) {
                auto &position = positions[i];
                auto &hitbox = hitboxs[i];

                if (!hitbox || !position || !hitbox.value().debug)
                    continue;

                // Dessiner le contour de la hitbox
                int leftX = position.value().x;
                int rightX = position.value().x + hitbox.value().width;
                int topY = position.value().y;
                int bottomY = position.value().y + hitbox.value().height;

                // Lignes verticales
                DrawLine(leftX, topY, leftX, bottomY, RED);
                DrawLine(rightX, topY, rightX, bottomY, RED);

                // Lignes horizontales
                DrawLine(leftX, topY, rightX, topY, RED);
                DrawLine(leftX, bottomY, rightX, bottomY, RED);
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

            for (size_t i = 0; i < drawables.size() && i < animations.size(); ++i) {
                auto &draw = drawables[i];
                auto &anim = animations[i];

                if (!draw || !anim)
                    continue;
                // Texture2D currFrame = anim.value().textureList.at(0).at(0);
                // Image image = GetImageData(currFrame);
                // ImageResize(&image, draw.value().resizeW, draw.value().resizeH);
                // // draw.value().texture = currFrame;
                draw.value().texture = anim.value().textureList.at(0).at(1);
                // à compléter (pour l'instant: image fixe)
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

            for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
                auto &pos = positions[i];
                auto &draw = drawables[i];

                if (!pos || !draw)
                    continue;

                Vector2 position = { pos.value().x, pos.value().y };

                DrawTextureV(draw.value().texture, position, WHITE);
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

            for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
                auto &pos = positions[i];
                auto &vel = velocities[i];


                if (!pos || !vel)
                    continue;

                pos.value().x += vel.value().vx;
                pos.value().y += vel.value().vy;
            }
        }

        asio::io_context io_context;
    protected:
    private:
        asio::ip::udp::socket _udp_socket;
        asio::ip::udp::endpoint _server_endpoint;
        char recv_buffer_[1024];

        Registry &r;

};

#endif /* !CLIENTSYSTEM_HPP_ */

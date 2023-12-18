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
#include "components/Controllable.hpp"
#include "components/Drawable.hpp"
#include "components/Velocity.hpp"
#include "components/Position.hpp"
#include "components/Clickable.hpp"
#include "components/Hitbox.hpp"
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
        ClientSystem(Registry *r, short server_port) : _udp_socket(io_context_), r(r)
        {
            _udp_socket.open(asio::ip::udp::v4());
            _server_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string("127.0.0.1"), server_port);

            start_receive();
        }

        ~ClientSystem()
        {
            send_disconnect();
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

            std::cout << "Send Disconnect" << std::endl;

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

            _udp_socket.send_to(asio::buffer(serialized_str), _server_endpoint);
        }

        void create_game()
        {
            CreateGameMessage msg;
            msg.header.type = MessageType::Create_Game;

            std::ostringstream archive_stream;
            boost::archive::text_oarchive archive(archive_stream);

            archive << msg;

            std::string serialized_str = archive_stream.str();

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
        \brief Handles data received from the server->

        \param error Boost ASIO error code, if any.
        \param bytes_transferred Number of bytes received.
        */
        void handle_receive_system(const std::error_code &error, std::size_t bytes_transferred)
        {
            if (!error)
            {
                std::string received_message(recv_buffer_, bytes_transferred);
                std::cout << "Received: " << received_message << std::endl;
            }
            start_receive();
        }

        /**
         * @brief Gère les clics de l'utilisateur->
         *
         * Ce système détecte les clics de souris et déclenche des actions
         * si un objet cliquable est touché.
         *
         * @param r Référence à l'objet Registry contenant les entités et composants.
         * @param event Événement SFML capturé.
         * @param window Fenêtre SFML pour la capture de la position de la souris.
         */
        void click_system() {
            std::string scene = r->getCurrentScene();
            Sparse_Array<Clickable> &clickables = r->getComponents<Clickable>(scene);
            Sparse_Array<Hitbox> &hitboxs = r->getComponents<Hitbox>(scene);
            Sparse_Array<Position> &positions = r->getComponents<Position>(scene);

            for (size_t i = 0; i < clickables.size() && i < hitboxs.size() && i < positions.size(); ++i) {
                auto &click = clickables[i];
                auto &hitbox = hitboxs[i];
                auto &position = positions[i];

                if (!hitbox || !click || !position) continue;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mouse = GetMousePosition();
                    if (mouse.x < position.value().x || mouse.x > (position.value().x + hitbox.value().width)) continue;
                    if (mouse.y < position.value().y || mouse.y > (position.value().y + hitbox.value().height)) continue;
                    click.value().proc(r);
                }
            }
        }

        void control_system() {
            std::string scene = r->getCurrentScene();
            Sparse_Array<Controllable> &controllables = r->getComponents<Controllable>(scene);
            Sparse_Array<Velocity> &velocities = r->getComponents<Velocity>(scene);

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
            std::string scene = r->getCurrentScene();
            Sparse_Array<Hitbox> &hitboxs = r->getComponents<Hitbox>(scene);
            Sparse_Array<Position> &positions = r->getComponents<Position>(scene);

            for (size_t i = 0; i < positions.size() && i < hitboxs.size(); ++i) {
                auto &position = positions[i];
                auto &hitbox = hitboxs[i];

                if (!hitbox || !position || !hitbox.value().debug) continue;

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

        void draw_system() {
            std::string scene = r->getCurrentScene();
            auto &positions = r->getComponents<Position>(scene);
            auto &drawables = r->getComponents<Drawable>(scene);

            for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
                auto &pos = positions[i];
                auto &draw = drawables[i];

                if (!pos || !draw)
                    continue;

                Vector2 position = { pos.value().x, pos.value().y };

                DrawTextureV(draw.value().texture, position, WHITE);
            }
        }

        void position_system() {
            std::string scene = r->getCurrentScene();
            Sparse_Array<Position> &positions = r->getComponents<Position>(scene);
            Sparse_Array<Velocity> &velocities = r->getComponents<Velocity>(scene);

            for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
                auto &pos = positions[i];
                auto &vel = velocities[i];


                if (!pos || !vel)
                    continue;

                pos.value().x += vel.value().vx;
                pos.value().y += vel.value().vy;
            }
        }

        asio::io_context io_context_;
    protected:
    private:
        asio::ip::udp::socket _udp_socket;
        asio::ip::udp::endpoint _server_endpoint;
        char recv_buffer_[1024];

        Registry *r;

};

#endif /* !CLIENTSYSTEM_HPP_ */

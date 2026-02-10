/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerSystem
*/

#ifndef SERVERSYSTEM_HPP_
#define SERVERSYSTEM_HPP_

#include "RaylibWrapper.hpp"
#include <asio.hpp>
#include <map>
#include <memory>

#include "Communication_Structures.hpp"
#include "ECS/Registry.hpp"
#include "WaveStructures.hpp"
#include "LogicSystems.hpp"

class ServerSystem {
    public:
        ServerSystem(Registry &r, short port);

        /*!
        \brief Handles data received from a client.

        \param error Boost ASIO error code, if any.
        \param bytes_transferred Number of bytes received.
        */
        void handle_client_system(Registry &r, const std::array<char, 1024>& message, std::size_t length);

        /**
         * @brief Main update loop for server-side systems.
         * @param r The registry containing entities and components.
         */
        void update(Registry &r);

        /**
         * @brief Broadcast the current state of entities to all connected clients.
         * @param r The registry.
         */
        void broadcast_ecs_transfert(Registry &r);

        /**
         * @brief Spawns an enemy of a specific type at a given position.
         */
        void spawn_enemy(Registry &r, EnemyType type, float x, float y);

        /**
         * @brief Update the wave system logic.
         */
        void update_waves(Registry &r, float dt);

        asio::io_service io_service;
    protected:
    private:
        std::unordered_map<std::string, size_t> clients_entity;
        std::unordered_map<size_t, size_t> client_server_entity_id;

        asio::ip::udp::socket _socket;
        std::array<char, 1024> _recvBuffer;
        asio::ip::udp::endpoint _remoteEndpoint;

        std::string localEndpoint;

        Registry &r;

        std::vector<EnemyWave> _waves;
        Logic::WaveState _waveState;

        // /*!
        // \brief Broadcast a message to every registered clients

        // \param message the string to send
        // */
        // void broadcast_message(const std::string& message);

        /*!
        \brief Starts receiving data from the network.
        */
        void startReceive();
};

#endif /* !SERVERSYSTEM_HPP_ */

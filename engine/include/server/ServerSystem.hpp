/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerSystem
*/

#ifndef SERVERSYSTEM_HPP_
#define SERVERSYSTEM_HPP_

#include <memory>
#include <asio.hpp>
#include <map>

#include "Communication_Structures.hpp"
#include "ECS/Registry.hpp"

class ServerSystem {
    public:
        ServerSystem(Registry &r, short port);

        /*!
        \brief Handles data received from a client.

        \param error Boost ASIO error code, if any.
        \param bytes_transferred Number of bytes received.
        */
        void handle_client_system(Registry &r, const std::array<char, 1024>& message, std::size_t length);

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

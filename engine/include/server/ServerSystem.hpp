/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerSystem
*/

#ifndef SERVERSYSTEM_HPP_
#define SERVERSYSTEM_HPP_

#include <memory>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <map>

#include "Communication_Structures.hpp"
#include "ECS/Registry.hpp"

using boost::asio::ip::udp;
using namespace boost::placeholders;

class ServerSystem {
    public:
        ServerSystem(Registry &r, short port);

        /*!
        \brief Handles data received from a client.

        \param error Boost ASIO error code, if any.
        \param bytes_transferred Number of bytes received.
        */
        void handle_client_system(Registry &r, const boost::system::error_code& error,
            std::size_t bytes_transferred);

        boost::asio::io_service io_service;
    protected:
    private:
        udp::socket _socket;
        std::array<char, 1024> _recvBuffer;
        udp::endpoint _remoteEndpoint;

        std::unordered_map<udp::endpoint, size_t> clients_entity;

        Registry &r;

        /*!
        \brief Handler to connect a client

        \param message the serialized data
        */
        std::string client_connect_handler(FirstConMessage &msg);

        /*!
        \brief Handler to disconnect a client

        \param message the serialized data
        */
        std::string client_disconnect_handler(std::string message);

        /*!
        \brief Broadcast a message to every registered clients

        \param message the string to send
        */
        void broadcast_message(const std::string& message);

        /*!
        \brief Starts receiving data from the network.
        */
        void startReceive();

        /*!
        \brief Handles sending data to a client.

        \param message Message to send.
        \param ec Boost ASIO error code, if any.
        \param bytes_transferred Number of bytes sent.
        */
        void handle_send(std::shared_ptr<std::string> message,
            const boost::system::error_code& ec,
            std::size_t bytes_transferred);
};

#endif /* !SERVERSYSTEM_HPP_ */

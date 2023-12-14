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

#include "ECS/Registry.hpp"

using boost::asio::ip::udp;
using namespace boost::placeholders;

class ServerSystem {
    public:
        ServerSystem(Registry *r, short port) : _socket(io_service, udp::endpoint(udp::v4(), port)), r(r) {
            startReceive();
        }

        /*!
        \brief Handles data received from a client.

        \param error Boost ASIO error code, if any.
        \param bytes_transferred Number of bytes received.
        */
        void handle_client(Registry *r, const boost::system::error_code& error,
            std::size_t bytes_transferred)
        {
            if (!error || error == boost::asio::error::message_size) {
                auto message = std::make_shared<std::string>(_recvBuffer.data(), bytes_transferred);

                std::cout << "Received: " << *message << std::endl;

                _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
                    boost::bind(&ServerSystem::handle_send, this, message,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
            }
        }

        /*!
        \brief Starts receiving data from the network.
        */
        void startReceive()
        {
            _socket.async_receive_from(
                boost::asio::buffer(_recvBuffer), _remoteEndpoint,
                boost::bind(&ServerSystem::handle_client, this,
                    r,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred)
            );
        }

        /*!
        \brief Handles sending data to a client.

        \param message Message to send.
        \param ec Boost ASIO error code, if any.
        \param bytes_transferred Number of bytes sent.
        */
        void handle_send(std::shared_ptr<std::string> message,
            const boost::system::error_code& ec,
            std::size_t bytes_transferred)
        {
            startReceive();
        }

        boost::asio::io_service io_service;
    protected:
    private:
        udp::socket _socket;
        std::array<char, 1024> _recvBuffer;
        udp::endpoint _remoteEndpoint;

        Registry *r;
};

#endif /* !SERVERSYSTEM_HPP_ */

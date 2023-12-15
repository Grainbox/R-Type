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

#include "Communication_Structures.hpp"
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
            std::cout << "-------------------------------------" << std::endl;
            std::cout << "Bytes received: " << bytes_transferred << std::endl;

            if (!error || error == boost::asio::error::message_size) {
                auto message = std::make_shared<std::string>(_recvBuffer.data(), bytes_transferred);

                std::cout << "Received data: " << *message << std::endl;

                std::istringstream archive_stream(*message);
                boost::archive::text_iarchive archive(archive_stream);
                FirstConMessage msg;
                archive >> msg;

                std::cout << "Deserialized message type: " << static_cast<int>(msg.header.type) << std::endl << std::endl;

                switch (msg.header.type) {
                    case MessageType::First_Con: {
                        Entity client = r->spawnEntity();
                        clients_entity[_remoteEndpoint] = client.getEntityId();

                        std::cout << "Client Connected, assigned on: " << client.getEntityId() << std::endl;
                        break;
                    }
                    case MessageType::Disconnect: {
                        DisconnectMessage msg;
                        std::istringstream archive_stream(*message);
                        boost::archive::text_iarchive archive(archive_stream);

                        archive >> msg;

                        r->killEntity(clients_entity[_remoteEndpoint], r->getCurrentScene());
                        clients_entity.erase(_remoteEndpoint);

                        std::cout << "Client Disconnected for reason: " << msg.reason << std::endl;
                        break;
                    }
                    case MessageType::Create_Game: {
                        std::cout << "Create Game" << std::endl;
                        break;
                    }
                    default:
                        std::cerr << "Unknown message type received!" << std::endl;
                }
                _socket.async_send_to(boost::asio::buffer("hello"), _remoteEndpoint,
                    boost::bind(&ServerSystem::handle_send, this, message,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
            }
            std::cout << "-------------------------------------" << std::endl;
        }

        boost::asio::io_service io_service;
    protected:
    private:
        udp::socket _socket;
        std::array<char, 1024> _recvBuffer;
        udp::endpoint _remoteEndpoint;

        std::unordered_map<udp::endpoint, size_t> clients_entity;

        Registry *r;

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
};

#endif /* !SERVERSYSTEM_HPP_ */

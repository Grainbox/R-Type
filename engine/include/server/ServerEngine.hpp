/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerEngine
*/

#ifndef SERVERENGINE_HPP_
#define SERVERENGINE_HPP_

#include "ECS/Registry.hpp"
#include "ServerSystem.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::udp;

class ServerEngine {
    public:
        ServerEngine(Registry *r, short port);

        void run() {
            io_service.run();
        }

    protected:
    private:
        Registry *r;

        boost::asio::io_service io_service;
        udp::socket _socket;
        std::array<char, 1024> _recvBuffer;
        udp::endpoint _remoteEndpoint;

        void startReceive();

        void handle_client(const boost::system::error_code& error,
            std::size_t bytes_transferred);

        void handle_send(std::shared_ptr<std::string> message,
            const boost::system::error_code& ec,
            std::size_t bytes_transferred);
};

#endif /* !SERVERENGINE_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerEngine
*/

#ifndef SERVERENGINE_HPP_
#define SERVERENGINE_HPP_

#ifdef _WIN32
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#define ENGINE_API
#endif

#include "ECS/Registry.hpp"
#include "ServerSystem.hpp"
#include "Engine.hpp"

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using boost::asio::ip::udp;
using namespace boost::placeholders;

/*!
 \class ServerEngine
 \brief Class managing the server engine.

 This class implements the server functionalities, including receiving and sending messages to clients.
*/
class ENGINE_API ServerEngine : public Engine {
    public:
        ServerEngine(Registry *r, short port);
        ~ServerEngine();
    protected:
    private:
        Registry *r;

        boost::asio::io_service io_service;
        udp::socket _socket;
        std::array<char, 1024> _recvBuffer;
        udp::endpoint _remoteEndpoint;

        void run();

        void startReceive();

        void handle_client(const boost::system::error_code& error,
            std::size_t bytes_transferred);

        void handle_send(std::shared_ptr<std::string> message,
            const boost::system::error_code& ec,
            std::size_t bytes_transferred);
};

#endif /* !SERVERENGINE_HPP_ */

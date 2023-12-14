/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerEngine
*/

#include "server/ServerEngine.hpp"

/*!
 \brief Constructor of ServerEngine.

 \param r Pointer to a Registry object.
 \param port Port number on which the server is listening.
*/
ServerEngine::ServerEngine(Registry *r, short port) :
    _socket(io_service, udp::endpoint(udp::v4(), port))
{
    this->r = r;

    std::cout << "Server listening on port: " << port << std::endl;

    this->run();
}

void ServerEngine::run()
{
    io_service.run();

    while (1) {
        this->startReceive();
    }
}

/*!
 \brief Starts receiving data from the network.
*/
void ServerEngine::startReceive()
{
    _socket.async_receive_from(
        boost::asio::buffer(_recvBuffer), _remoteEndpoint,
        boost::bind(&ServerEngine::handle_client, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}

/*!
 \brief Handles data received from a client.

 \param error Boost ASIO error code, if any.
 \param bytes_transferred Number of bytes received.
*/
void ServerEngine::handle_client(const boost::system::error_code& error,
    std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        auto message = std::make_shared<std::string>(_recvBuffer.data(), bytes_transferred);

        std::cout << "Received: " << *message << std::endl;

        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
            boost::bind(&ServerEngine::handle_send, this, message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}

/*!
 \brief Handles sending data to a client.

 \param message Message to send.
 \param ec Boost ASIO error code, if any.
 \param bytes_transferred Number of bytes sent.
*/
void ServerEngine::handle_send(std::shared_ptr<std::string> message,
    const boost::system::error_code& ec,
    std::size_t bytes_transferred)
{
    startReceive();
}

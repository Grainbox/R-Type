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
#include <asio.hpp>
#include <iostream>

class ServerEngine
{
public:
    ServerEngine(Registry *r);

protected:
private:
    Registry *r;
    asio::io_service _io_service;
    asio::ip::udp::socket _socket;
    char recv_buffer_[1024];
    asio::ip::udp::endpoint _remote_endpoint;

    void run();

    void do_receive()
    {
        int debug = 0;
        _socket.async_receive_from(
            asio::buffer(recv_buffer_), _remote_endpoint,
            [this](std::error_code ec, std::size_t bytes_recvd)
            {
                if (!ec && bytes_recvd > 0)
                {
                    handle_receive(std::string(recv_buffer_, bytes_recvd), _remote_endpoint);
                    do_receive();
                }
            });
    }

    void handle_receive(const std::string &data, const asio::ip::udp::endpoint &endpoint)
    {
        std::cout << "Received packet: " << data << " from " << endpoint << std::endl;

        if (data == "new_connection" || data == "hello")
        {
            send_to("welcome", endpoint);
        }
    }

    void send_to(const std::string &message, const asio::ip::udp::endpoint &target_endpoint)
    {
        _socket.async_send_to(asio::buffer(message), target_endpoint,
                              [](std::error_code, std::size_t) {
                              });
        std::cout << "Sent packet: " << message << " to " << target_endpoint << std::endl;
    }
};

#endif /* !SERVERENGINE_HPP_ */

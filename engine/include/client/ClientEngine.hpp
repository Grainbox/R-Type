/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ClientEngine
*/

#ifndef CLIENTENGINE_HPP_
#define CLIENTENGINE_HPP_

#include "ClientSystem.hpp"
#include "ECS/Registry.hpp"
#include <asio.hpp>

#include <SFML/Graphics.hpp>

class ClientEngine
{
public:
    ClientEngine(Registry *r, short server_port);

protected:
private:
    sf::RenderWindow window;
    Registry *r;
    ClientSystem system;

    asio::io_context io_context_;
    asio::ip::udp::socket _udp_socket;
    asio::ip::udp::endpoint _server_endpoint;
    char recv_buffer_[1024];

    void start_receive();
    void handle_receive(const std::error_code &error, std::size_t bytes_transferred);
    void send_hello();

    void run();

    void processEvents();

    void update();

    void render();
};

#endif /* !CLIENTENGINE_HPP_ */

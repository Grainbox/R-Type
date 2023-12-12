/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerEngine
*/

#include "server/ServerEngine.hpp"

ServerEngine::ServerEngine(Registry *r)
    : r(r), _io_service(), _socket(_io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), 4242))
{
    run();
}

void ServerEngine::run()
{
    do_receive();
    _io_service.run();
}

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
ServerEngine::ServerEngine(Registry *r, short port) : system(*r, port)
{
    this->r = r;

    std::cout << "Server listening on port: " << port << std::endl;

    this->run();
}

/*!
 \brief Destructor of ServerEngine.
*/
ServerEngine::~ServerEngine()
{
}

void ServerEngine::run()
{
    system.io_service.run();

    while (1);
}
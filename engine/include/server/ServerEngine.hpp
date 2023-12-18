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

/*!
 \class ServerEngine
 \brief Class managing the server engine.

 This class implements the server functionalities, including receiving and sending messages to clients.
*/
class ENGINE_API ServerEngine : public Engine {
    public:
        ServerEngine(Registry &r, short port);
        ~ServerEngine();
    protected:
    private:
        Registry &r;

        ServerSystem system;

        void run();
};

#endif /* !SERVERENGINE_HPP_ */

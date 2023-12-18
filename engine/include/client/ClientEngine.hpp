/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ClientEngine
*/

#ifndef CLIENTENGINE_HPP_
#define CLIENTENGINE_HPP_

#ifdef _WIN32
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#define ENGINE_API
#endif

#include "ClientSystem.hpp"
#include "ECS/Registry.hpp"
#include "Engine.hpp"

/*!
 \class ClientEngine
 \brief Class managing the clients engines.

 This class implements the client functionalities, including receiving and sending messages to server.
*/
class ENGINE_API ClientEngine : public Engine {
    public:
        ClientEngine(Registry &r, short server_port);
        ~ClientEngine();

    protected:
    private:
        Registry &r;
        ClientSystem system;

        void run();

        void processEvents();

        void update();

        void render();
};

#endif /* !CLIENTENGINE_HPP_ */

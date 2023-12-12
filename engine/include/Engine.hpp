/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#ifdef _WIN32
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#define ENGINE_API
#endif

#define SERVER_PORT 1024

#include "ECS/Registry.hpp"
#include "client/ClientEngine.hpp"
#include "server/ServerEngine.hpp"

/*!
 \struct EngineConfig
 \brief Struct containing engine configuration.

 This struct allows you to add config for the engine.
*/
struct EngineConfig
{
    bool isServer;
    Registry *r;
};

/*!
 \class Engine
 \brief Class managing the engine.

 This class is exposed for shared library and is dispatching client / server engines.
*/
class ENGINE_API Engine
{
public:
    Engine(EngineConfig config);
    ~Engine();

protected:
private:
};

#endif /* !ENGINE_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerEngine
*/

#include "server/ServerEngine.hpp"
#include <chrono>
#include <thread>

/*!
 \brief Constructor of ServerEngine.

 \param r Pointer to a Registry object.
 \param port Port number on which the server is listening.
*/
ServerEngine::ServerEngine(Registry &r, short port) : r(r), system(r, port)
{
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
    // Start ASIO processing in a separate thread to not block the game loop
    std::thread asio_thread([this]() {
        this->system.io_service.run();
    });

    const int TPS = 60;
    const std::chrono::nanoseconds tick_duration(1000000000LL / TPS);
    auto next_tick = std::chrono::steady_clock::now();

    while (true) {
        auto now = std::chrono::steady_clock::now();
        
        if (now >= next_tick) {
            // Update systems
            system.update(r);
            
            next_tick += tick_duration;
        }

        // Avoid pegged CPU if ahead of schedule
        auto sleep_time = next_tick - std::chrono::steady_clock::now();
        if (sleep_time > std::chrono::milliseconds(1)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    if (asio_thread.joinable())
        asio_thread.join();
}
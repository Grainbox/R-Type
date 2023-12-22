/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ClientEngine
*/

#include "client/ClientEngine.hpp"

/*!
 \brief Constructor of ClientEngine.

 \param r Pointer to a Registry object.
 \param port Port number on which the client is connecting.
*/
ClientEngine::ClientEngine(Registry &r, short server_port)
    : r(r), system(r, server_port)
{
    system.send_first_con();

    run();
}

/*!
 \brief Destructor of ClientEngine.
*/
ClientEngine::~ClientEngine()
{
    system.send_disconnect();
    CloseWindow();
    CloseAudioDevice();
    system.io_context.stop();
}

/*!
 \brief Runs the game loop and call the ECS.
*/
void ClientEngine::run()
{
    while (!WindowShouldClose())
    {
        this->processEvents();
        this->update();
        this->render();

        system.io_context.poll();
    }
}

/*!
 \brief Process the raylib events and dispatch it on event related systems.
*/
void ClientEngine::processEvents()
{
    system.control_system();
    system.key_detection_system();
    system.click_system();
    system.reactCursor_system();
}

/*!
 \brief Updates the window state by calling systems.
*/
void ClientEngine::update()
{
    system.position_system();
    system.Health_system();
    system.Move_system();
    system.hitbox_system();
    system.collision_reaction_system();
}

/*!
 \brief Render entities on the window by calling related systems.
*/
void ClientEngine::render()
{
    BeginDrawing();

    ClearBackground(BLACK);
    system.update_sprites_system();
    system.draw_hitbox_system();
    system.draw_system();
    system.SoundWrapper_system();
    system.Text_system();

    EndDrawing();
}

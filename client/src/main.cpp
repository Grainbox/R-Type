/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "client/ClientEngine.hpp"
#include "MainView.hpp"
#include "GameView.hpp"

void mainMenu(Registry &r)
{
    MainView mainview(r);
    mainview.process();
}

void gameScene(Registry &r)
{
    GameView gameview(r);
    gameview.process();
}

void create_entity(EntityComponents server_ent, Registry &r, MessageHandlerData &data)
{
    std::cout << "Creating entity" << std::endl;

    Entity ent(r.spawnEntity(r.getCurrentScene()));
    data.client_server_entity_id[server_ent.entity_id] = ent.getEntityId();

    if (server_ent.controllable) {
        Controllable control = server_ent.controllable.value();
        r.addComponent<Controllable>(ent, control, r.getCurrentScene());
    }
    if (server_ent.drawable) {
        Drawable drawable(server_ent.drawable.value().spritePath);
        r.addComponent<Drawable>(ent, drawable, r.getCurrentScene());
    }
    if (server_ent.position) {
        Position position = server_ent.position.value();
        r.addComponent<Position>(ent, position, r.getCurrentScene());
    }
    if (server_ent.velocity) {
        Velocity velocity = server_ent.velocity.value();
        r.addComponent<Velocity>(ent, velocity, r.getCurrentScene());
    }
}

void update_entity(EntityComponents server_ent, Registry &r, MessageHandlerData &data, size_t ent)
{
    std::cout << "Updating Entity" << std::endl;

    if (server_ent.controllable) {
        Controllable control = server_ent.controllable.value();
        r.addComponent<Controllable>(ent, control, r.getCurrentScene());
    }
    if (server_ent.drawable) {
        Drawable drawable(server_ent.drawable.value().spritePath);
        r.addComponent<Drawable>(ent, drawable, r.getCurrentScene());
    }
    if (server_ent.position) {
        Position position = server_ent.position.value();
        r.addComponent<Position>(ent, position, r.getCurrentScene());
    }
    if (server_ent.velocity) {
        Velocity velocity = server_ent.velocity.value();
        r.addComponent<Velocity>(ent, velocity, r.getCurrentScene());
    }
}

void receive_entities(Registry &r, size_t entity_id, MessageHandlerData data)
{
    if (data.type != MessageType::ECS_Transfert)
        return;

    std::cout << "ECS Transfert" << std::endl;
    TransfertECSMessage msg;
    std::istringstream archive_stream(data.message);
    boost::archive::text_iarchive archive(archive_stream);

    archive >> msg;

    for (auto it : msg.entities) {
        std::cout << "Server Entity ID: " << it.entity_id << std::endl;

        if (size_t entity_id = (data.client_server_entity_id.find(it.entity_id)) == data.client_server_entity_id.end()) {
            create_entity(it, r, data);
        } else {
            update_entity(it, r, data, entity_id);
        }
    }

    std::cout << "Transfered" << std::endl;
}

void setupRegistry(Registry &r)
{
    mainMenu(r);

    Entity udp = r.spawnEntity("gameScene");

    ReceiveUDP receiveUDP(r.registerComScript(std::bind(receive_entities,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3))
    );

    r.addComponent<ReceiveUDP>(udp, receiveUDP, "gameScene");

    // gameScene(r);
}

int main()
{
    try
    {
        Registry r("mainMenu");

        int winWidth = 800;
        int winHeigth = 600;
        InitAudioDevice();
        InitWindow(winWidth, winHeigth, "My Engine");
        SetTargetFPS(60);

        setupRegistry(r);

        ClientEngine engine(r, SERVER_PORT);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

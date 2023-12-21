/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "server/ServerEngine.hpp"

void client_connect_handler(Registry &r, MessageHandlerData data)
{
    std::istringstream archive_stream(data.message);
    boost::archive::text_iarchive archive(archive_stream);
    FirstConMessage msg;
    archive >> msg;

    Entity client = r.spawnEntity(r.getCurrentScene());

    Position pos(100, 0);
    Controllable controls;
    controls.setKeyboardKey(&controls.Up, KEY_UP);
    controls.setKeyboardKey(&controls.Down, KEY_DOWN);
    controls.setKeyboardKey(&controls.Left, KEY_LEFT);
    controls.setKeyboardKey(&controls.Right, KEY_RIGHT);
    Velocity vel(0, 0);
    Drawable draw("assets/entity_1.png", true);

    r.addComponent<Drawable>(client, draw, "game");
    r.addComponent<Position>(client, pos, "game");
    r.addComponent<Controllable>(client, controls, "game");
    r.addComponent<Velocity>(client, vel, "game");

    data.clients_entity[data._remoteEndpoint] = client.getEntityId();

    std::cout << "Client Connected, assigned on: " << client.getEntityId() << std::endl;
}

void client_disconnect_handler(Registry &r, MessageHandlerData data)
{
    DisconnectMessage msg;
    std::istringstream archive_stream(data.message);
    boost::archive::text_iarchive archive(archive_stream);

    archive >> msg;

    std::string serialized_str = archive_stream.str();

    r.killEntity(data.clients_entity[data._remoteEndpoint], r.getCurrentScene());
    data.clients_entity.erase(data._remoteEndpoint);

    std::cout << "Client Disconnected for reason: " << msg.reason << std::endl;
}

void create_game_handler(Registry &r, MessageHandlerData data)
{
    TransfertECSMessage msg;
    msg.header.type = MessageType::ECS_Transfert;

    std::list<size_t> deadEntities = r.getDeadEntities();

    for (size_t i = 0; i < r.getNextEntityId(); i++) {
        auto it = std::find(deadEntities.begin(), deadEntities.end(), i);

        if (!deadEntities.empty() && it == deadEntities.end())
            continue;

        EntityComponents comps;

        comps.entity_id = i;

        comps.controllable = r.get_boost_entity_component<Controllable>(i);
        comps.drawable = r.get_boost_entity_component<Drawable>(i);
        comps.position = r.get_boost_entity_component<Position>(i);
        comps.velocity = r.get_boost_entity_component<Velocity>(i);

        msg.entities.push_back(comps);
    }

    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << msg;

    std::string serialized_str = archive_stream.str();

    // Broadcast entities
    for (const auto& client : data.clients_entity) {
        std::cout << client.first << std::endl;
        data._socket.async_send_to(
            asio::buffer(serialized_str), client.first,
            [](const std::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
                } else {
                    std::cerr << "Error sending message: " << error.message() << std::endl;
                }
            }
        );
    }
}

void update_entity(Registry &r, MessageHandlerData data)
{
    std::istringstream archive_stream(data.message);
    boost::archive::text_iarchive archive(archive_stream);
    TransfertECSMessage msg;
    archive >> msg;

    for (auto it : msg.entities) {
        std::cout << "Updating Entity" << std::endl;

        if (it.controllable) {
            Controllable control = it.controllable.value();
            r.addComponent<Controllable>(it.entity_id, control, r.getCurrentScene());
        }
        if (it.drawable) {
            Drawable drawable(it.drawable.value().spritePath);
            r.addComponent<Drawable>(it.entity_id, drawable, r.getCurrentScene());
        }
        if (it.position) {
            Position position = it.position.value();
            r.addComponent<Position>(it.entity_id, position, r.getCurrentScene());
        }
        if (it.velocity) {
            Velocity velocity = it.velocity.value();
            r.addComponent<Velocity>(it.entity_id, velocity, r.getCurrentScene());
        }
    }

    std::ostringstream new_archive_stream;
    boost::archive::text_oarchive new_archive(new_archive_stream);
    new_archive << msg;

    std::string serialized_str = archive_stream.str();

    for (const auto& client : data.clients_entity) {
        std::cout << client.first << std::endl;
        data._socket.async_send_to(
            asio::buffer(serialized_str), client.first,
            [](const std::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
                } else {
                    std::cerr << "Error sending message: " << error.message() << std::endl;
                }
            }
        );
    }
}

void mainUDPHandler(Registry &r, size_t entity_id, MessageHandlerData data)
{
    if (data.type == MessageType::First_Con)
        return client_connect_handler(r, data);
    if (data.type == MessageType::Disconnect)
        return client_disconnect_handler(r, data);
    if (data.type == MessageType::Create_Game)
        return create_game_handler(r, data);
    if (data.type == MessageType::ECS_Transfert)
        return update_entity(r, data);

    // Respond to caller
    // data._socket.async_send_to(
    //     asio::buffer(serialized_str), data._remoteEndpoint,
    //     [](const std::error_code& error, std::size_t bytes_transferred) {
    //         if (!error) {
    //             std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
    //         } else {
    //             std::cerr << "Error sending message: " << error.message() << std::endl;
    //         }
    //     }
    // );
}

void setupRegistry(Registry &r)
{
    Entity udp = r.spawnEntity("game");

    ReceiveUDP receiveUDP(r.registerComScript(std::bind(mainUDPHandler,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3))
    );

    r.addComponent<ReceiveUDP>(udp, receiveUDP, "game");
}

int main()
{
    try
    {
        Registry r("game");

        setupRegistry(r);

        ServerEngine engine(r, SERVER_PORT);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

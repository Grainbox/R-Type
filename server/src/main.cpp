/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "server/ServerEngine.hpp"

void client_connect_handler(MessageHandlerData data)
{
    std::istringstream archive_stream(data.message);
    boost::archive::text_iarchive archive(archive_stream);
    FirstConMessage msg;
    archive >> msg;

    // Entity client = r.spawnEntity(r.getCurrentScene());
    // clients_entity[_remoteEndpoint] = client.getEntityId();

    // std::cout << "Client Connected, assigned on: " << _remoteEndpoint << "->" << client.getEntityId() << std::endl;
}

void client_disconnect_handler(MessageHandlerData data)
{
    DisconnectMessage msg;
    std::istringstream archive_stream(data.message);
    boost::archive::text_iarchive archive(archive_stream);

    archive >> msg;

    std::string serialized_str = archive_stream.str();

    // r.killEntity(clients_entity[_remoteEndpoint], r.getCurrentScene());
    // clients_entity.erase(_remoteEndpoint);

    std::cout << "Client Disconnected for reason: " << msg.reason << std::endl;
}

void mainUDPHandler(Registry &r, size_t entity_id, MessageHandlerData data)
{
    if (data.type == MessageType::First_Con)
        return client_connect_handler(data);
    if (data.type == MessageType::Disconnect)
        return client_disconnect_handler(data);

    TransfertECSMessage msg;
    msg.header.type = MessageType::ECS_Transfert;

    std::list<size_t> deadEntities = r.getDeadEntities();

    for (size_t i = 0; i < r.getNextEntityId(); i++) {
        auto it = std::find(deadEntities.begin(), deadEntities.end(), i);

        if (!deadEntities.empty() && it == deadEntities.end())
            continue;

        EntityComponents comps;

        comps.entity_id = i;
        // comps.clickable = r.get_entity_component<Clickable>(i);
        comps.controllable = r.get_boost_entity_component<Controllable>(i);
        comps.drawable = r.get_boost_entity_component<Drawable>(i);
        // comps.hitbox = r.get_entity_component<Hitbox>(i);
        // comps.kb_input = r.get_entity_component<KeyboardInput>(i);
        comps.position = r.get_boost_entity_component<Position>(i);
        // comps.react_cursor = r.get_entity_component<ReactCursor>(i);
        comps.velocity = r.get_boost_entity_component<Velocity>(i);
        msg.entities.push_back(comps);
    }

    std::ostringstream archive_stream(data.message);
    boost::archive::text_oarchive archive(archive_stream);
    archive << msg;

    std::string serialized_str = archive_stream.str();

    std::cout << "Sending: " << serialized_str << std::endl;

    data._socket->async_send_to(
        asio::buffer(serialized_str), *data._remoteEndpoint,
        [](const std::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
            } else {
                std::cerr << "Error sending message: " << error.message() << std::endl;
            }
        }
    );
}

void setupRegistry(Registry &r)
{
    Entity player = r.spawnEntity("mainMenu");

    Position pos(100, 0);
    Controllable controls;
    controls.setKeyboardKey(&controls.Up, KEY_UP);
    controls.setKeyboardKey(&controls.Down, KEY_DOWN);
    controls.setKeyboardKey(&controls.Left, KEY_LEFT);
    controls.setKeyboardKey(&controls.Right, KEY_RIGHT);
    Velocity vel(0, 0);
    Drawable draw("assets/entity_1.png", true);

    r.addComponent<Drawable>(player, draw, "mainMenu");
    r.addComponent<Position>(player, pos, "mainMenu");
    r.addComponent<Controllable>(player, controls, "mainMenu");
    r.addComponent<Velocity>(player, vel, "mainMenu");

    Entity udp = r.spawnEntity("mainMenu");

    ReceiveUDP receiveUDP(r.registerComScript(std::bind(mainUDPHandler,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3))
    );

    r.addComponent<ReceiveUDP>(udp, receiveUDP, "mainMenu");
}

int main()
{
    try
    {
        Registry r("mainMenu");

        setupRegistry(r);

        ServerEngine engine(r, SERVER_PORT);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

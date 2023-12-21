/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** main
*/

#include <iostream>
#include <ostream>

#include "server/ServerEngine.hpp"

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
}

    /*!
    \brief Handler to create a game

    \param message the serialized data
    */
std::string create_game_handler(Registry &r, size_t entity_id, std::string message, MessageType type)
{
    std::cout << "Create Game" << std::endl;

    if (type != MessageType::Create_Game) {
        return "";
    }

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

    std::ostringstream archive_stream(message);
    boost::archive::text_oarchive archive(archive_stream);
    archive << msg;

    std::string serialized_str = archive_stream.str();

    std::cout << "Sending: " << serialized_str << std::endl;

    return serialized_str;
}

int main()
{
    try
    {
        Registry r("mainMenu");

        setupRegistry(r);

        Entity udp = r.spawnEntity("mainMenu");

        ReceiveUDP receiveUDP(r.registerComScript(std::bind(create_game_handler,
                std::placeholders::_1,
                std::placeholders::_2,
                std::placeholders::_3,
                std::placeholders::_4))
        );

        r.addComponent<ReceiveUDP>(udp, receiveUDP, "mainMenu");

        ServerEngine engine(r, SERVER_PORT);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** SetupRegistry
*/

#include "SetupRegistry.hpp"
#include "components/AI.hpp"

SetupRegistry::SetupRegistry(Registry &r) : r(r)
{
    Entity udp = r.spawnEntity(r.getCurrentScene());

    ReceiveUDP receiveUDP(r.registerComScript(
        std::bind(&SetupRegistry::mainUDPHandler, this,
                  std::placeholders::_1,
                  std::placeholders::_2,
                  std::placeholders::_3)));

    r.addComponent<ReceiveUDP>(udp, receiveUDP, r.getCurrentScene());
};

std::optional<std::string> SetupRegistry::find_key_for_value(
    const std::unordered_map<std::string, size_t> &clients_entity,
    size_t value)
{
    for (const auto &pair : clients_entity)
    {
        if (pair.second == value)
        {
            return pair.first;
        }
    }
    return std::nullopt;
}

asio::ip::udp::endpoint SetupRegistry::string_to_endpoint(
    const std::string &str)
{
    size_t colon_pos = str.find(':');
    if (colon_pos == std::string::npos)
    {
        throw std::invalid_argument("Invalid endpoint format");
    }

    std::string ip_str = str.substr(0, colon_pos);
    std::string port_str = str.substr(colon_pos + 1);

    asio::ip::udp::endpoint endpoint(asio::ip::make_address(ip_str),
                                     std::stoi(port_str));
    return endpoint;
}

void SetupRegistry::client_connect_handler(Registry &r,
                                           MessageHandlerData data)
{
    std::istringstream archive_stream(data.message);
    boost::archive::text_iarchive archive(archive_stream);
    FirstConMessage msg;
    archive >> msg;

    Entity client = r.spawnEntity(r.getCurrentScene());

    Position pos(client.getEntityId() * 150, 0);
    MoveBehavior behavior;
    behavior.setControllable(true);
    behavior.addKeyboardKey(behavior.UpInput, KEY_UP);
    behavior.addKeyboardKey(behavior.DownInput, KEY_DOWN);
    behavior.addKeyboardKey(behavior.LeftInput, KEY_LEFT);
    behavior.addKeyboardKey(behavior.RightInput, KEY_RIGHT);
    behavior.addKeyboardKey(behavior.UpInput, KEY_W);
    behavior.addKeyboardKey(behavior.DownInput, KEY_S);
    behavior.addKeyboardKey(behavior.LeftInput, KEY_A);
    behavior.addKeyboardKey(behavior.RightInput, KEY_D);
    behavior.setMoveSpeed(4);
    Velocity vel(0, 0);
    Drawable draw("assets/entity_1.png", true);

    r.addComponent<Drawable>(client, draw, r.getCurrentScene());
    r.addComponent<Position>(client, pos, r.getCurrentScene());
    r.addComponent<MoveBehavior>(client, behavior, r.getCurrentScene());
    r.addComponent<Velocity>(client, vel, r.getCurrentScene());
    r.addComponent<Hitbox>(client, Hitbox(100, 50, true), r.getCurrentScene());
    r.addComponent<HitTag>(client, HitTag(HitTag::TAG1), r.getCurrentScene());

    std::string endpoint = data._remoteEndpoint.address().to_string() + ":" +
                           std::to_string(data._remoteEndpoint.port());

    data.clients_entity[endpoint] = client.getEntityId();

    std::cout << "Client Connected, assigned on: " << client.getEntityId() << std::endl;

    std::ostringstream new_archive_stream;
    boost::archive::text_oarchive new_archive(new_archive_stream);

    msg.endpoint = endpoint;
    new_archive << msg;

    std::string serialized_str = new_archive_stream.str();

    // Respond to caller
    data._socket.async_send_to(
        asio::buffer(serialized_str), data._remoteEndpoint,
        [](const std::error_code &error, std::size_t bytes_transferred)
        {
            if (!error)
            {
                std::cout << "Message sent successfully, bytes transferred: "
                          << bytes_transferred << std::endl;
            }
            else
            {
                std::cerr << "Error sending message: " << error.message() << std::endl;
            }
        });
}

void SetupRegistry::client_disconnect_handler(Registry &r,
                                              MessageHandlerData data)
{
    DisconnectMessage msg;
    std::istringstream archive_stream(data.message);
    boost::archive::text_iarchive archive(archive_stream);

    archive >> msg;

    std::string endpoint = data._remoteEndpoint.address().to_string() + ":" +
                           std::to_string(data._remoteEndpoint.port());

    size_t entity_to_kill = data.clients_entity[endpoint];

    r.killEntity(data.clients_entity[endpoint], r.getCurrentScene());
    data.clients_entity.erase(endpoint);

    std::cout << "Client Disconnected for reason: " << msg.reason << std::endl;

    std::ostringstream new_archive_stream;
    boost::archive::text_oarchive new_archive(new_archive_stream);

    msg.disconnected_entity = entity_to_kill;
    new_archive << msg;

    std::string serialized_str = new_archive_stream.str();

    for (const auto &client : data.clients_entity)
    {
        data._socket.async_send_to(
            asio::buffer(serialized_str), string_to_endpoint(client.first),
            [](const std::error_code &error, std::size_t bytes_transferred)
            {
                if (!error)
                {
                    std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
                }
                else
                {
                    std::cerr << "Error sending message: " << error.message() << std::endl;
                }
            });
    }
}

void SetupRegistry::create_game_handler(Registry &r, MessageHandlerData data)
{
    TransfertECSMessage msg;
    msg.header.type = MessageType::ECS_Transfert;

    std::list<size_t> deadEntities = r.getDeadEntities();

    // The Wave System in ServerSystem will handle dynamic enemy spawning.
    std::cout << "Game handler called" << std::endl;

    for (size_t i = 0; i < r.getNextEntityId(); i++)
    {
        auto it = std::find(deadEntities.begin(), deadEntities.end(), i);

        if (!deadEntities.empty() && it == deadEntities.end())
            continue;

        EntityComponents comps;

        comps.entity_id = i;
        comps.scene = r.getCurrentScene();

        auto result = find_key_for_value(data.clients_entity, i);

        if (result)
        {
            comps.assigned_endpoint = result.value();
        }
        else
        {
            comps.assigned_endpoint = "none";
        }

        comps.controllable = {}; // Controllable is no longer used
        comps.moveBehavior = r.get_boost_entity_component<MoveBehavior>(i);
        comps.drawable = r.get_boost_entity_component<Drawable>(i);
        comps.position = r.get_boost_entity_component<Position>(i);
        comps.velocity = r.get_boost_entity_component<Velocity>(i);
        comps.boss = r.get_boost_entity_component<Boss>(i);
        comps.health = r.get_boost_entity_component<Health>(i);
        comps.hitbox = r.get_boost_entity_component<Hitbox>(i);
        comps.hitTag = r.get_boost_entity_component<HitTag>(i);

        msg.entities.push_back(comps);
    }

    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << msg;

    std::string serialized_str = archive_stream.str();

    // Broadcast entities
    for (const auto &client : data.clients_entity)
    {
        data._socket.async_send_to(
            asio::buffer(serialized_str), string_to_endpoint(client.first),
            [](const std::error_code &error, std::size_t bytes_transferred)
            {
                if (!error)
                {
                    std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
                }
                else
                {
                    std::cerr << "Error sending message: " << error.message() << std::endl;
                }
            });
    }
}

void SetupRegistry::update_entity(Registry &r, MessageHandlerData data)
{
    std::istringstream archive_stream(data.message);
    boost::archive::text_iarchive archive(archive_stream);
    TransfertECSMessage msg;
    archive >> msg;

    for (auto it : msg.entities)
    {
        std::cout << "Updating Entity" << std::endl;

        if (it.moveBehavior)
        {
            MoveBehavior control = it.moveBehavior.value();
            r.addComponent<MoveBehavior>(it.entity_id, control, r.getCurrentScene());
        }
        if (it.drawable)
        {
            Drawable drawable(it.drawable.value().spritePath);
            r.addComponent<Drawable>(it.entity_id, drawable, r.getCurrentScene());
        }
        if (it.position)
        {
            Position position = it.position.value();
            r.addComponent<Position>(it.entity_id, position, r.getCurrentScene());
        }
        if (it.velocity)
        {
            Velocity velocity = it.velocity.value();
            r.addComponent<Velocity>(it.entity_id, velocity, r.getCurrentScene());
        }
        if (it.hitbox)
        {
            Hitbox hitbox = it.hitbox.value();
            r.addComponent<Hitbox>(it.entity_id, hitbox, r.getCurrentScene());
        }
        if (it.hitTag)
        {
            HitTag hitTag = it.hitTag.value();
            r.addComponent<HitTag>(it.entity_id, hitTag, r.getCurrentScene());
        }
    }

    std::ostringstream new_archive_stream;
    boost::archive::text_oarchive new_archive(new_archive_stream);
    new_archive << msg;

    std::string serialized_str = archive_stream.str();

    for (const auto &client : data.clients_entity)
    {
        data._socket.async_send_to(
            asio::buffer(serialized_str), string_to_endpoint(client.first),
            [](const std::error_code &error, std::size_t bytes_transferred)
            {
                if (!error)
                {
                    std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
                }
                else
                {
                    std::cerr << "Error sending message: " << error.message() << std::endl;
                }
            });
    }
}

void SetupRegistry::mainUDPHandler(Registry &r, size_t entity_id, MessageHandlerData data)
{
    if (data.type == MessageType::First_Con)
        return client_connect_handler(r, data);
    if (data.type == MessageType::Disconnect)
        return client_disconnect_handler(r, data);
    if (data.type == MessageType::Create_Game)
        return create_game_handler(r, data);
    if (data.type == MessageType::ECS_Transfert)
        return update_entity(r, data);
}

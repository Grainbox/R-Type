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
    Controllable controls;
    controls.addKeyboardKey(controls.Up, KEY_UP);
    controls.addKeyboardKey(controls.Down, KEY_DOWN);
    controls.addKeyboardKey(controls.Left, KEY_LEFT);
    controls.addKeyboardKey(controls.Right, KEY_RIGHT);
    controls.addKeyboardKey(controls.Up, KEY_W);
    controls.addKeyboardKey(controls.Down, KEY_S);
    controls.addKeyboardKey(controls.Left, KEY_A);
    controls.addKeyboardKey(controls.Right, KEY_D);
    Velocity vel(0, 0);
    Drawable draw("assets/entity_1.png", true);

    r.addComponent<Drawable>(client, draw, r.getCurrentScene());
    r.addComponent<Position>(client, pos, r.getCurrentScene());
    r.addComponent<Controllable>(client, controls, r.getCurrentScene());
    r.addComponent<Velocity>(client, vel, r.getCurrentScene());

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

    // Spawn some AI enemies for testing if it's the first time
    static bool enemiesSpawned = false;
    if (!enemiesSpawned) {
        // Sinusoidal Enemy
        Entity e1 = r.spawnEntity(r.getCurrentScene());
        r.addComponent<Position>(e1, Position(700, 200), r.getCurrentScene());
        r.addComponent<Velocity>(e1, Velocity(-100, 0), r.getCurrentScene());
        r.addComponent<Drawable>(e1, Drawable("assets/entity_2.png"), r.getCurrentScene());
        r.addComponent<AI>(e1, AI(AIMode::Sinusoidal, 2.0f, 50.0f), r.getCurrentScene());
        r.addComponent<Health>(e1, Health(50), r.getCurrentScene());

        // ZigZag Enemy
        Entity e2 = r.spawnEntity(r.getCurrentScene());
        r.addComponent<Position>(e2, Position(800, 400), r.getCurrentScene());
        r.addComponent<Velocity>(e2, Velocity(-150, 50), r.getCurrentScene());
        r.addComponent<Drawable>(e2, Drawable("assets/entity_2.png"), r.getCurrentScene());
        r.addComponent<AI>(e2, AI(AIMode::ZigZag, 1.5f, 100.0f), r.getCurrentScene());
        r.addComponent<Health>(e2, Health(50), r.getCurrentScene());

        // Homing Enemy
        Entity e3 = r.spawnEntity(r.getCurrentScene());
        r.addComponent<Position>(e3, Position(750, 300), r.getCurrentScene());
        r.addComponent<Velocity>(e3, Velocity(0, 0), r.getCurrentScene());
        r.addComponent<Drawable>(e3, Drawable("assets/entity_2.png"), r.getCurrentScene());
        r.addComponent<AI>(e3, AI(AIMode::Homing, 1.0f, 80.0f), r.getCurrentScene());
        r.addComponent<Health>(e3, Health(75), r.getCurrentScene());

        // Boss Entity
        Entity boss = r.spawnEntity(r.getCurrentScene());
        r.addComponent<Position>(boss, Position(700, 300), r.getCurrentScene());
        r.addComponent<Velocity>(boss, Velocity(-50, 0), r.getCurrentScene());
        r.addComponent<Drawable>(boss, Drawable("assets/entity_2.png"), r.getCurrentScene());
        r.addComponent<AI>(boss, AI(AIMode::Sinusoidal, 1.0f, 30.0f), r.getCurrentScene());
        r.addComponent<Health>(boss, Health(300), r.getCurrentScene());
        r.addComponent<Boss>(boss, Boss(300, 3), r.getCurrentScene());
        
        enemiesSpawned = true;
    }

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

        comps.controllable = r.get_boost_entity_component<Controllable>(i);
        comps.drawable = r.get_boost_entity_component<Drawable>(i);
        comps.position = r.get_boost_entity_component<Position>(i);
        comps.velocity = r.get_boost_entity_component<Velocity>(i);
        comps.boss = r.get_boost_entity_component<Boss>(i);
        comps.health = r.get_boost_entity_component<Health>(i);

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

        if (it.controllable)
        {
            Controllable control = it.controllable.value();
            r.addComponent<Controllable>(it.entity_id, control, r.getCurrentScene());
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

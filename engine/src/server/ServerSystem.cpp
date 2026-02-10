/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerSystem
*/

#include "server/ServerSystem.hpp"
#include <cmath>
#include "components/AI.hpp"

ServerSystem::ServerSystem(Registry &r, short port) : _socket(io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), r(r)
{
    // Define Waves
    // Wave 1: 3 Sinusoidal
    EnemyWave wave1;
    wave1.steps.push_back({EnemyType::Sinusoidal, 3, 2.0f, 800, 300, 200});
    wave1.timeBeforeNextWave = 5.0f;
    _waves.push_back(wave1);

    // Wave 2: 2 ZigZag
    EnemyWave wave2;
    wave2.steps.push_back({EnemyType::ZigZag, 2, 3.0f, 800, 300, 150});
    wave2.timeBeforeNextWave = 5.0f;
    _waves.push_back(wave2);

    // Wave 3: Mix
    EnemyWave wave3;
    wave3.steps.push_back({EnemyType::Homing, 2, 4.0f, 850, 300, 100});
    wave3.steps.push_back({EnemyType::Sinusoidal, 2, 2.0f, 800, 100, 0});
    wave3.timeBeforeNextWave = 10.0f;
    _waves.push_back(wave3);

    // Wave 4: Boss
    EnemyWave wave4;
    wave4.steps.push_back({EnemyType::Boss, 1, 0.0f, 700, 300, 0});
    wave4.timeBeforeNextWave = 60.0f;
    _waves.push_back(wave4);

    startReceive();
}

void ServerSystem::handle_client_system(Registry &r,
    const std::array<char, 1024>& receivedMessage, std::size_t length)
{
    std::string message(receivedMessage.begin(), receivedMessage.end() + length);
    std::cout << "-------------------------------------" << std::endl;

    std::istringstream archive_stream(message);
    boost::archive::text_iarchive archive(archive_stream);
    FirstConMessage msg;
    archive >> msg;

    std::string returnMessage = "ERROR";

    std::cout << "Deserialized message type: " << static_cast<int>(msg.header.type) << std::endl << std::endl;

    std::string scene = r.getCurrentScene();
    Sparse_Array<ReceiveUDP> &udpComp = r.getComponents<ReceiveUDP>(scene);

    for (size_t i = 0; i < udpComp.dense_size(); i++) {
        size_t entity_id = udpComp.get_entity_at(i);
        auto &udp = udpComp.dense_at(i);

        MessageHandlerData data = {message, msg.header.type, _socket, _remoteEndpoint, clients_entity, client_server_entity_id, localEndpoint};
        r.getComScript(udp.script_id)(r, entity_id, data);
    }

    std::cout << "-------------------------------------" << std::endl;
}

// void ServerSystem::broadcast_message(const std::string& message)
// {
    // for (const auto& client : r.clients_entity) {
    //     std::cout << client.first << std::endl;
    //     _socket.async_send_to(
    //         asio::buffer(message), client.first,
    //         [](const std::error_code& error, std::size_t bytes_transferred) {
    //             if (!error) {
    //                 std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
    //             } else {
    //                 std::cerr << "Error sending message: " << error.message() << std::endl;
    //             }
    //         }
    //     );
    // }
// }

void ServerSystem::update(Registry &r)
{
    float dt = 1.0f / 60.0f; // Approx DeltaTime for 60 TPS

    Logic::update_boss_phases(r, r.getCurrentScene());
    Logic::update_ai_movement(r, r.getCurrentScene(), dt);
    Logic::position_system(r, r.getCurrentScene(), dt);

    update_waves(r, dt);
    broadcast_ecs_transfert(r);
}

void ServerSystem::spawn_enemy(Registry &r, EnemyType type, float x, float y)
{
    Entity e = r.spawnEntity(r.getCurrentScene());
    r.addComponent<Position>(e, Position(x, y), r.getCurrentScene());
    r.addComponent<Hitbox>(e, Hitbox(100, 50, true), r.getCurrentScene());
    r.addComponent<HitTag>(e, HitTag(HitTag::TAG2), r.getCurrentScene());

    switch (type) {
        case EnemyType::Sinusoidal:
            r.addComponent<Velocity>(e, Velocity(-100, 0), r.getCurrentScene());
            r.addComponent<Drawable>(e, Drawable("assets/r-typesheet5.gif", true), r.getCurrentScene());
            r.addComponent<AnimatedDraw>(e, AnimatedDraw("assets/r-typesheet5.gif", 16, 1, 0.05f), r.getCurrentScene());
            r.addComponent<AI>(e, AI(AIMode::Sinusoidal, 2.0f, 50.0f), r.getCurrentScene());
            r.addComponent<Health>(e, Health(50), r.getCurrentScene());
            break;
        case EnemyType::ZigZag:
            r.addComponent<Velocity>(e, Velocity(-150, 50), r.getCurrentScene());
            r.addComponent<Drawable>(e, Drawable("assets/r-typesheet22.gif", true), r.getCurrentScene());
            r.addComponent<AnimatedDraw>(e, AnimatedDraw("assets/r-typesheet22.gif", 16, 1, 0.05f), r.getCurrentScene());
            r.addComponent<AI>(e, AI(AIMode::ZigZag, 1.5f, 100.0f), r.getCurrentScene());
            r.addComponent<Health>(e, Health(50), r.getCurrentScene());
            break;
        case EnemyType::Homing:
            r.addComponent<Velocity>(e, Velocity(0, 0), r.getCurrentScene());
            r.addComponent<Drawable>(e, Drawable("assets/r-typesheet26.gif", true), r.getCurrentScene());
            r.addComponent<AnimatedDraw>(e, AnimatedDraw("assets/r-typesheet26.gif", 16, 1, 0.05f), r.getCurrentScene());
            r.addComponent<AI>(e, AI(AIMode::Homing, 1.0f, 80.0f), r.getCurrentScene());
            r.addComponent<Health>(e, Health(75), r.getCurrentScene());
            break;
        case EnemyType::Boss:
            r.addComponent<Velocity>(e, Velocity(-50, 0), r.getCurrentScene());
            r.addComponent<Drawable>(e, Drawable("assets/r-typesheet30.gif", true), r.getCurrentScene());
            r.addComponent<AnimatedDraw>(e, AnimatedDraw("assets/r-typesheet30.gif", 16, 1, 0.05f), r.getCurrentScene());
            r.addComponent<AI>(e, AI(AIMode::Sinusoidal, 1.0f, 30.0f), r.getCurrentScene());
            r.addComponent<Health>(e, Health(300), r.getCurrentScene());
            r.addComponent<Boss>(e, Boss(300, 3), r.getCurrentScene());
            break;
    }
}

void ServerSystem::update_waves(Registry &r, float dt)
{
    Logic::update_waves(r, r.getCurrentScene(), dt, _waves, _waveState, std::bind(&ServerSystem::spawn_enemy, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

void ServerSystem::broadcast_ecs_transfert(Registry &r)
{
    TransfertECSMessage msg;
    msg.header.type = MessageType::ECS_Transfert;

    std::string scene = r.getCurrentScene();
    auto &positions = r.getComponents<Position>(scene);
    
    for (size_t i = 0; i < positions.dense_size(); ++i) {
        Entity entity_id = positions.get_entity_at(i);
        EntityComponents comps;
        comps.entity_id = entity_id;
        comps.scene = scene;
        comps.position = positions.dense_at(i);
        comps.velocity = r.get_boost_entity_component<Velocity>(entity_id);
        comps.drawable = r.get_boost_entity_component<Drawable>(entity_id);
        
        msg.entities.push_back(comps);
    }

    if (msg.entities.empty()) return;

    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << msg;
    std::string serialized_str = archive_stream.str();

    for (const auto &client : clients_entity) {
        asio::ip::udp::endpoint endpoint;
        try {
            size_t colon_pos = client.first.find(':');
            endpoint = asio::ip::udp::endpoint(asio::ip::make_address(client.first.substr(0, colon_pos)), std::stoi(client.first.substr(colon_pos + 1)));
            
            _socket.async_send_to(asio::buffer(serialized_str), endpoint, 
                [](const std::error_code&, std::size_t){});
        } catch (...) {}
    }
}

void ServerSystem::startReceive()
{
    _socket.async_receive_from(
        asio::buffer(_recvBuffer), _remoteEndpoint,
        [this](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                handle_client_system(r, _recvBuffer, bytes_recvd);
            }
            this->startReceive();
        });
}

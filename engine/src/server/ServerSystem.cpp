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
    std::string scene = r.getCurrentScene();
    auto &ais = r.getComponents<AI>(scene);
    auto &positions = r.getComponents<Position>(scene);
    auto &velocities = r.getComponents<Velocity>(scene);
    auto &bosses = r.getComponents<Boss>(scene);
    auto &healths = r.getComponents<Health>(scene);
    auto &controllables = r.getComponents<Controllable>(scene);

    float dt = 1.0f / 60.0f; // Approx DeltaTime for 60 TPS

    // Update Boss phases based on health
    for (size_t i = 0; i < bosses.dense_size(); ++i) {
        Entity boss_id = bosses.get_entity_at(i);
        auto &boss = bosses.dense_at(i);
        auto health = healths[boss_id];
        auto ai = ais[boss_id];

        if (health && ai) {
            boss.currentHealth = health->currentHealth;
            int newPhase = boss.calculatePhase();
            
            if (newPhase != boss.currentPhase && newPhase < boss.healthSegments) {
                boss.currentPhase = newPhase;
                // Phase transition: increase speed and change pattern
                if (ai->mode == AIMode::Sinusoidal) {
                    ai->frequency += 0.5f;  // Faster oscillation
                    ai->amplitude += 10.0f; // Larger movement
                } else if (ai->mode == AIMode::ZigZag) {
                    ai->frequency -= 0.2f;  // Faster direction changes
                    ai->amplitude += 20.0f; // Faster movement
                }
            }
        }
    }

    for (size_t i = 0; i < ais.dense_size(); ++i) {
        Entity entity_id = ais.get_entity_at(i);
        auto &ai = ais.dense_at(i);
        auto pos = positions[entity_id];
        auto vel = velocities[entity_id];

        if (!pos) continue;

        if (!ai.initialized) {
            ai.startY = pos->y;
            ai.initialized = true;
        }

        ai.timer += dt;

        switch (ai.mode) {
            case AIMode::Sinusoidal:
                pos->y = ai.startY + std::sin(ai.timer * ai.frequency) * ai.amplitude;
                break;
            case AIMode::ZigZag:
                // Change direction every 'frequency' seconds
                if (std::fmod(ai.timer, ai.frequency * 2.0f) < ai.frequency) {
                    if (vel) vel->vy = std::abs(ai.amplitude);
                } else {
                    if (vel) vel->vy = -std::abs(ai.amplitude);
                }
                break;
            case AIMode::Homing:
                // Find nearest player (entity with Controllable component)
                {
                    float nearestDist = std::numeric_limits<float>::max();
                    Position* targetPos = nullptr;

                    for (size_t j = 0; j < controllables.dense_size(); ++j) {
                        Entity player_id = controllables.get_entity_at(j);
                        auto playerPos = positions[player_id];
                        
                        if (playerPos) {
                            float dx = playerPos->x - pos->x;
                            float dy = playerPos->y - pos->y;
                            float dist = std::sqrt(dx * dx + dy * dy);
                            
                            if (dist < nearestDist) {
                                nearestDist = dist;
                                targetPos = &(*playerPos);
                                ai.targetEntityId = player_id;
                            }
                        }
                    }

                    // Move toward target
                    if (targetPos && vel && nearestDist > 0.1f) {
                        float dx = targetPos->x - pos->x;
                        float dy = targetPos->y - pos->y;
                        float dist = std::sqrt(dx * dx + dy * dy);
                        
                        // Normalize and apply speed (amplitude = speed)
                        vel->vx = (dx / dist) * ai.amplitude;
                        vel->vy = (dy / dist) * ai.amplitude;
                    }
                }
                break;
            default:
                break;
        }

        // Apply basic velocity if present (for X movement)
        if (vel) {
            pos->x += vel->vx * dt;
            pos->y += vel->vy * dt;
        }
    }

    // Broadcast changes to all clients
    broadcast_ecs_transfert(r);
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

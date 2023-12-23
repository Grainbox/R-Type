/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerGameScene
*/

#ifndef SERVERGAMESCENE_HPP_
#define SERVERGAMESCENE_HPP_

#include "client/ClientEngine.hpp"

class ServerGameScene {
    public:
        ServerGameScene(Registry &r) : r(r) {
            this->process();
        };

        void process()
        {
            Entity udp = r.spawnEntity("gameScene");
            Entity udp2 = r.spawnEntity("mainMenu");

            ReceiveUDP receiveUDP(r.registerComScript(
                    std::bind(&ServerGameScene::handleUDP, this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3))
            );

            r.addComponent<ReceiveUDP>(udp, receiveUDP, "gameScene");
            r.addComponent<ReceiveUDP>(udp2, receiveUDP, "mainMenu");
        }

        void create_entity(EntityComponents server_ent, Registry &r, MessageHandlerData &data)
        {
            std::cout << "Creating entity" << std::endl;

            Entity ent(r.spawnEntity(server_ent.scene));
            data.client_server_entity_id[server_ent.entity_id] = ent.getEntityId();

            if (server_ent.controllable && server_ent.assigned_endpoint == data.localEndpoint) {
                Controllable control = server_ent.controllable.value();
                r.addComponent<Controllable>(ent, control, server_ent.scene);
            }
            if (server_ent.drawable) {
                Drawable drawable(server_ent.drawable.value().spritePath);
                r.addComponent<Drawable>(ent, drawable, server_ent.scene);
            }
            if (server_ent.position) {
                Position position = server_ent.position.value();
                r.addComponent<Position>(ent, position, server_ent.scene);
            }
            if (server_ent.velocity) {
                Velocity velocity = server_ent.velocity.value();
                r.addComponent<Velocity>(ent, velocity, server_ent.scene);
            }
            std::cout << "Entity created at: " << ent.getEntityId() << std::endl;
        }

        void update_entity(EntityComponents server_ent, Registry &r, MessageHandlerData &data, size_t ent)
        {
            std::cout << "Updating Entity" << std::endl;

            // if (server_ent.controllable && server_ent.assigned_endpoint == data.localEndpoint) {
            //     Controllable control = server_ent.controllable.value();
            //     r.addComponent<Controllable>(ent, control, r.getCurrentScene());
            // }
            // if (server_ent.drawable) {
            //     Drawable drawable(server_ent.drawable.value().spritePath);
            //     r.addComponent<Drawable>(ent, drawable, r.getCurrentScene());
            // }
            if (server_ent.position) {
                auto comp = r.get_entity_component<Position>(ent);

                if (comp) {
                    auto &pos = comp->get();
                    pos.x = server_ent.position.value().x;
                    pos.y = server_ent.position.value().y;
                }
            }
            // if (server_ent.velocity) {
            //     Velocity velocity = server_ent.velocity.value();
            //     r.addComponent<Velocity>(ent, velocity, r.getCurrentScene());
            // }
        }

        void receive_entities(Registry &r, size_t entity_id, MessageHandlerData data)
        {
            std::cout << "ECS Transfert" << std::endl;
            TransfertECSMessage msg;
            std::istringstream archive_stream(data.message);
            boost::archive::text_iarchive archive(archive_stream);

            archive >> msg;

            for (auto it : msg.entities) {
                if (data.client_server_entity_id.find(it.entity_id) != data.client_server_entity_id.end() && r.getCurrentScene() == it.scene) {
                    update_entity(it, r, data, data.client_server_entity_id[it.entity_id]);
                } else {
                    create_entity(it, r, data);
                }
            }

            std::cout << "Transfered" << std::endl;
        }

        void handleUDP(Registry &r, size_t entity_id, MessageHandlerData data)
        {
            if (data.type == MessageType::ECS_Transfert)
                return receive_entities(r, entity_id, data);
            if (data.type == MessageType::First_Con) {
                std::istringstream archive_stream(data.message);
                boost::archive::text_iarchive archive(archive_stream);
                FirstConMessage msg;
                archive >> msg;

                data.localEndpoint = msg.endpoint;
            }
            if (data.type == MessageType::Disconnect) {
                std::istringstream archive_stream(data.message);
                boost::archive::text_iarchive archive(archive_stream);
                DisconnectMessage msg;
                archive >> msg;

                if (data.client_server_entity_id.find(msg.disconnected_entity) != data.client_server_entity_id.end()) {
                    r.killEntity(data.client_server_entity_id[msg.disconnected_entity], r.getCurrentScene());
                    data.client_server_entity_id.erase(msg.disconnected_entity);
                }
            }
        }

    protected:
    private:
        Registry &r;
};

#endif /* !SERVERGAMESCENE_HPP_ */

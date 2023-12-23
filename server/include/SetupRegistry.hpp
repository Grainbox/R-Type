/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** SetupRegistry
*/

#ifndef SETUPREGISTRY_HPP_
#define SETUPREGISTRY_HPP_

#include "server/ServerEngine.hpp"

class SetupRegistry {
    public:
        SetupRegistry(Registry &r);

    private:

        std::optional<std::string> find_key_for_value(
            const std::unordered_map<std::string, size_t>& clients_entity,
            size_t value);

        asio::ip::udp::endpoint string_to_endpoint(const std::string& str);

        void client_connect_handler(Registry &r, MessageHandlerData data);

        void client_disconnect_handler(Registry &r, MessageHandlerData data);

        void create_game_handler(Registry &r, MessageHandlerData data);

        void update_entity(Registry &r, MessageHandlerData data);

        void mainUDPHandler(Registry &r, size_t entity_id,
            MessageHandlerData data);

        Registry &r;
};

#endif /* !SETUPREGISTRY_HPP_ */

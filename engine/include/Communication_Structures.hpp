/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Communication_Structures
*/

#ifndef COMMUNICATION_STRUCTURES_HPP_
#define COMMUNICATION_STRUCTURES_HPP_

#include <string>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>

enum class MessageType : uint8_t {
    First_Con = 0,
    Disconnect = 1,
    Create_Game = 2,
    ECS_Transfert = 3,
};

struct MessageHeader {
    MessageType type;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & type;
    }
};

struct DisconnectMessage {
    MessageHeader header;

    std::string reason;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
        ar & reason;
    }
};

struct FirstConMessage {
    MessageHeader header;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
    }
};

struct CreateGameMessage {
    MessageHeader header;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
    }
};

struct TransfertECSMessage {
    MessageHeader header;

    std::unordered_map<std::type_index, std::any> comps;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
    }
};


#endif /* !COMMUNICATION_STRUCTURES_HPP_ */

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
#include <boost/serialization/optional.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>
#include <typeindex>

#include "components/ComponentIncluder.hpp"
#include "Communication_Headers.hpp"

struct DisconnectMessage {
    MessageHeader header;

    size_t disconnected_entity;
    std::string reason;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
        ar & disconnected_entity;
        ar & reason;
    }
};

struct FirstConMessage {
    MessageHeader header;

    std::string endpoint;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
        ar & endpoint;
    }
};

struct CreateGameMessage {
    MessageHeader header;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
    }
};

struct EntityComponents {
    size_t entity_id;
    std::string scene;

    std::string assigned_endpoint;

    boost::optional<Controllable> controllable;
    boost::optional<Drawable> drawable;
    boost::optional<ReceiveUDP> receiveUdp;
    boost::optional<HitTag> hitTag;
    boost::optional<Position> position;
    boost::optional<Velocity> velocity;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & entity_id;
        ar & scene;
        ar & assigned_endpoint;
        ar & controllable;
        ar & drawable;
        ar & receiveUdp;
        ar & hitTag;
        ar & position;
        ar & velocity;
    }
};

struct TransfertECSMessage {
    MessageHeader header;

    std::vector<EntityComponents> entities;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
        ar & entities;
    }
};


#endif /* !COMMUNICATION_STRUCTURES_HPP_ */

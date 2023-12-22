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

struct EntityComponents {
    size_t entity_id;

    // std::optional<Clickable> clickable;
    boost::optional<Controllable> controllable;
    boost::optional<Drawable> drawable;
    boost::optional<ReceiveUDP> receiveUdp;
    // std::optional<Hitbox> hitbox;
    boost::optional<HitTag> hitTag;
    // std::optional<KeyboardInput> kb_input;
    // boost::optional<OnCollision> onCollision;
    boost::optional<Position> position;
    // std::optional<ReactCursor> react_cursor;
    boost::optional<Velocity> velocity;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & entity_id;
        // ar & clickable;
        ar & controllable;
        ar & drawable;
        ar & receiveUdp;
        // ar & hitbox;
        ar & hitTag;
        // ar & kb_input;
        // ar & onCollision;
        ar & position;
        // ar & react_cursor;
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

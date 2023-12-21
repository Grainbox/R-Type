/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Communication_Headers
*/

#ifndef COMMUNICATION_HEADERS_HPP_
#define COMMUNICATION_HEADERS_HPP_

#include <cstdint>

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

#endif /* !COMMUNICATION_HEADERS_HPP_ */

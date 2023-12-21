/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ReceiveUDP
*/

#ifndef RECEIVEUDP_HPP_
#define RECEIVEUDP_HPP_

#include <boost/serialization/serialization.hpp>
#include <cstddef>

class ReceiveUDP {
    public:
        ReceiveUDP() {};
        ReceiveUDP(size_t script_id) : script_id(script_id) {};

        size_t script_id;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & script_id;
        }

        friend class boost::serialization::access;
    protected:
    private:
};

#endif /* !RECEIVEUDP_HPP_ */

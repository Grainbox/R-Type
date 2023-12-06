/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <cstddef>

class Entity {
public:
    using type = size_t;

    explicit Entity() : _id(0) {}

    Entity(size_t id) : _id(id) {}

    Entity::type getEntityId() const {
        return _id;
    }

    Entity::type setEntityId(Entity::type id) {
        this->_id = id;
        return this->_id;
    }

    operator size_t() const { return _id; };

protected:
private:
    size_t _id;
};

#endif /* !ENTITY_HPP_ */

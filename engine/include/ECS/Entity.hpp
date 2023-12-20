/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <cstddef>

/*!
 \class Entity
 \brief Class representing an entity.

 This class defines an entity with a unique ID. It provides functionalities to get and set the entity's ID.
*/
class Entity {
public:
    using type = size_t;

    /*!
     \brief Default constructor for Entity.

     Initializes an entity with an ID of 0.
    */
    explicit Entity() : _id(0) {}

    /*!
     \brief Constructor for Entity with a specific ID.

     \param id The unique ID for the entity.
    */
    Entity(size_t id) : _id(id) {}

    Entity(size_t id, size_t server_side_id) : _id(id), _server_side_id(server_side_id) {}

    /*!
     \brief Get the ID of the entity.

     \return The ID of the entity.
    */
    Entity::type getEntityId() const {
        return _id;
    }

    /*!
     \brief Get the server side ID of the entity.

     \return The server side ID of the entity.
    */
    Entity::type getServerSideID() const {
        return _server_side_id;
    }

    /*!
     \brief Set the ID of the entity.

     \param id The new ID for the entity.
     \return The updated ID of the entity.
    */
    Entity::type setEntityId(Entity::type id) {
        this->_id = id;
        return this->_id;
    }

    /*!
     \brief Set the server side ID of the entity.

     \param id The new server side ID for the entity.
     \return The updated server side ID of the entity.
    */
    Entity::type setServerSideID(Entity::type id) {
        this->_server_side_id = id;
        return this->_server_side_id;
    }

    /*!
     \brief Conversion operator to size_t.

     Allows the Entity to be implicitly converted to a size_t representing its ID.

     \return The ID of the entity.
    */
    operator size_t() const { return _id; };

protected:
private:
    size_t _id; ///< Unique identifier for the entity.
    size_t _server_side_id; ///< Unique identifier for the server side entity.
};

#endif /* !ENTITY_HPP_ */

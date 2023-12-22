/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** OnCollision
*/

#ifndef ONCOLLISION_HPP_
#define ONCOLLISION_HPP_

#include "ECS/Registry.hpp"
#include <boost/serialization/serialization.hpp>
#include "Hitbox.hpp"

/*!
 \class OnCollision
 \brief Component that is used on entities that need to react to identified collisions.
*/
class OnCollision {
    public:
        OnCollision() = default;

        void addReaction(HitTag::hitTag tag, size_t script_id_input)
        {
            reactionsList.push_back(std::make_pair(tag, script_id_input));
        }

        std::list<std::pair<HitTag::hitTag, size_t>> reactionsList;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & reactionsList;
        }

        friend class boost::serialization::access;
    protected:
    private:
};

#endif /* !ONCOLLISION_HPP_ */

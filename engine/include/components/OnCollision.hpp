/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** OnCollision
*/

#ifndef ONCOLLISION_HPP_
#define ONCOLLISION_HPP_

#include "ECS/Registry.hpp"
#include "Hitbox.hpp"
#include <map>

class OnCollision {
    public:
        OnCollision() = default;

        void addReaction(HitTag::hitTag tag, size_t script_id_input)
        {
            reactionsList.push_back(std::make_pair(tag, script_id_input));
        }

        std::list<std::pair<HitTag::hitTag, size_t>> reactionsList;
        // OnCollision(Registry &r, Hitbox hitbox, HitTag::hitTag tag, size_t script_id_input) {
        //     std::cout << "ok" << std::endl;
        //     for (auto id : hitbox.getCollisionList()) {
        //         std::cout << "id: " << id << std::endl;
        //         auto entity_hitBox = r.get_entity_component<Hitbox>(id);
        //         HitTag entity_hitTag = entity_hitBox->get().getHitTag();
        //         if (tag == entity_hitTag.tag)
        //             script_id = script_id_input;
        //         // if (tag == entity_hitBox.value().get().getHitTag().tag) {
        //         // }
        //     }
        //     std::cout << "-----------------------------------------" << std::endl;
        // }
        // size_t script_id;
        // std::function<void(Registry &, size_t)> proc;
    protected:
    private:
};

#endif /* !ONCOLLISION_HPP_ */

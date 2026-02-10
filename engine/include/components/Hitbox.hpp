/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Hitbox
*/

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

    #include <iostream>
    #include <list>
    #include <utility>
    #include <boost/serialization/serialization.hpp>
    #include <boost/serialization/list.hpp>
    #include <boost/serialization/utility.hpp>
    #include "HitTag.hpp"

class Hitbox {
    public:
        Hitbox() = default;
        Hitbox(size_t x, size_t y) : width(x), height(y) {};
        Hitbox(size_t x, size_t y, bool debugs) : width(x), height(y), debug(debugs) {};

        void setHitTag(HitTag new_tag) { _hitTag = new_tag; };
        HitTag getHitTag(void) { return _hitTag; };
        std::list<std::pair<size_t, HitTag::hitTag>> getCollisionList(void) { return _collisions; };
        void clearCollisionList(void) { _collisions.clear(); };
        void enterCollision(size_t id, HitTag::hitTag tag) { _collisions.push_back(std::make_pair(id, tag)); };

        // void onCollision(Registry &r, HitTag::hitTag tag, const std::function<void(Registry &, size_t)>& func)
        // {
        //     std::cout << "ok" << std::endl;
        //     for (auto id : _collisions) {
        //         std::cout << "id: " << id << std::endl;
        //         auto entity_hitBox = r.get_entity_component<Hitbox>(id);
        //         HitTag entity_hitTag = entity_hitBox->get().getHitTag();
        //         if (tag == entity_hitBox.value().get().getHitTag().tag)
        //             proc = func;
        //     }
        //     std::cout << "-----------------------------------------" << std::endl;
        // }

        size_t width = 0;
        size_t height = 0;
        bool debug = false;
        // std::function<void(Registry &, size_t)> proc;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & width;
            ar & height;
            ar & debug;
            ar & _hitTag;
            ar & _collisions;
            // ar & proc;
        }

        friend class boost::serialization::access;
    protected:
    private:
        HitTag _hitTag;
        std::list<std::pair<size_t, HitTag::hitTag>> _collisions;
};

#endif /* !HITBOX_HPP_ */

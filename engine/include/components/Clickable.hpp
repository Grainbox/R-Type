/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Clickable
*/

#ifndef CLICKABLE_HPP_
#define CLICKABLE_HPP_

    #include "ECS/Registry.hpp"
    #include <boost/serialization/serialization.hpp>

class Clickable {
    public:
        Clickable(const std::function<void(Registry &)>& func) {
            proc = func;
        }
        std::function<void(Registry &)> proc;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & proc;
        }

        friend class boost::serialization::access;
    protected:
    private:
};

#endif /* !CLICKABLE_HPP_ */

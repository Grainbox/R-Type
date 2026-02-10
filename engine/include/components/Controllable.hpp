/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Controllable
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

#include <vector>
#include <algorithm>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

/*!
 \class Controllable
 \brief Component that is used on entities that can be controlled by user.
*/
class Controllable {
    public:
        void setKeyboardKey(std::vector<int> &moveKeys, int newKey) {
            moveKeys.clear();
            moveKeys.push_back(newKey);
        }
        void addKeyboardKey(std::vector<int> &moveKeys, int newKey) {
            if (std::find(moveKeys.begin(), moveKeys.end(), newKey) == moveKeys.end())
                moveKeys.push_back(newKey);
        }
        std::vector<int> Up;
        std::vector<int> Down;
        std::vector<int> Left;
        std::vector<int> Right;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & Up;
            ar & Down;
            ar & Left;
            ar & Right;
        }

        friend class boost::serialization::access;
    protected:
    private:
};

#endif /* !CONTROLLABLE_HPP_ */

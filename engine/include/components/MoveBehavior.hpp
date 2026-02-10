/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** MoveBehavior
*/

#ifndef MOVEBEHAVIOR_HPP_
#define MOVEBEHAVIOR_HPP_

#include <vector>
#include <algorithm>
#include "ECS/Registry.hpp"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

/*!
 \class MoveBehavior
 \brief Component that add rules to entities movements.
*/
class MoveBehavior {
    public:
        MoveBehavior() = default;

        void setControllable(bool isControllable) { _controllable = isControllable; };
        bool isControllable(void) const { return _controllable; };
        void setKeyboardKey(std::vector<int> &moveKeys, int newKey) {
            moveKeys.clear();
            moveKeys.push_back(newKey);
        };
        void addKeyboardKey(std::vector<int> &moveKeys, int newKey) {
            if (std::find(moveKeys.begin(), moveKeys.end(), newKey) == moveKeys.end())
                moveKeys.push_back(newKey);
        };

        std::vector<int> UpInput;
        std::vector<int> DownInput;
        std::vector<int> LeftInput;
        std::vector<int> RightInput;
        bool PressUp = false;
        bool PressDown = false;
        bool PressLeft = false;
        bool PressRight = false;

        void setConstMov(int vx, int vy) { constMovX = vx; constMovY = vy; };
        void setConstMovX(int vx) { constMovX = vx; };
        void setConstMovY(int vy) { constMovY = vy; };

        int constMovX = 0;
        int constMovY = 0;

        unsigned int getMoveSpeed(void) { return _moveSpeed; };
        void setMoveSpeed(unsigned int new_moveSpeed) { _moveSpeed = new_moveSpeed; };

        void setOffScreenMov(bool new_value) { _offScreenMov = new_value; };
        bool getOffScreenMov(void) { return _offScreenMov; };

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & _controllable;
            ar & _offScreenMov;
            ar & constMovX;
            ar & constMovY;
            ar & _moveSpeed;
            ar & UpInput;
            ar & DownInput;
            ar & LeftInput;
            ar & RightInput;
        }

        friend class boost::serialization::access;
    protected:
    private:
        bool _controllable = false;
        bool _offScreenMov = true;
        // std::pair<int, int> _moveSpeed;
        unsigned int _moveSpeed = 0;
};

#endif /* !MOVEBEHAVIOR_HPP_ */

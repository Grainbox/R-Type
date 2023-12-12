/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Controllable
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

#include <SFML/Graphics.hpp>

/*!
 \class Controllable
 \brief Component that is used on entities that can be controlled by user.
*/
class Controllable {
    public:
        void setKeyboardKey(sf::Keyboard::Key *moveKey, sf::Keyboard::Key newKey) {
            *moveKey = newKey;
        }
        sf::Keyboard::Key Up = sf::Keyboard::Unknown;
        sf::Keyboard::Key Down = sf::Keyboard::Unknown;
        sf::Keyboard::Key Left = sf::Keyboard::Unknown;
        sf::Keyboard::Key Right = sf::Keyboard::Unknown;
    protected:
    private:
};

#endif /* !CONTROLLABLE_HPP_ */

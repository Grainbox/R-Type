/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <string>
#include <SFML/Graphics.hpp>

#include "Exceptions.hpp"

/*!
 \class Drawable
 \brief Component that is used on entities that can be rendered on the window.
*/
class Drawable {
    public:
        Drawable(std::string spritePath) {
            if (!this->texture.loadFromFile(spritePath)) {
                throw LoadAssetException("Failed to load asset: " + spritePath);
            }
        };

        sf::Texture texture;
        sf::Sprite sprite;
    protected:
    private:
};

#endif /* !DRAWABLE_HPP_ */

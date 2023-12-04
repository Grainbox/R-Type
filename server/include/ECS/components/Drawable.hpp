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

class Drawable {
    public:
        Drawable(std::string spritePath) {
            if (!texture.loadFromFile(spritePath)) {
                throw LoadAssetException("Failed to load asset: " + spritePath);
            }
            sprite.setTexture(texture);
        };

        sf::Texture texture;
        sf::Sprite sprite;
    protected:
    private:
};

#endif /* !DRAWABLE_HPP_ */

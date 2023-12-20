/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <string>
#include <raylib.h>

#include "Exceptions.hpp"

/*!
 \class Drawable
 \brief Component that is used on entities that can be rendered on the window.
*/
class Drawable {
    public:
        Drawable(std::string spritePath) {
            this->texture = LoadTexture(spritePath.c_str());
            if (!this->texture.id) {
                throw LoadAssetException("Failed to load asset: " + spritePath);
            }
        };
        Drawable(std::string spritePath, int resizeWidth, int resizeHeight) {
            Image image = LoadImage(spritePath.c_str());
            ImageResizeNN(&image, resizeWidth, resizeHeight);
            this->texture = LoadTextureFromImage(image);
            UnloadImage(image);
            if (!this->texture.id) {
                throw LoadAssetException("Failed to load asset: " + spritePath);
            }
        };
        Drawable(Texture2D newTexture) {
            this->texture = newTexture;
            if (!this->texture.id) {
                throw LoadAssetException("Failed to load texture");
            }
        };

        Texture2D texture;
    protected:
    private:
};

#endif /* !DRAWABLE_HPP_ */

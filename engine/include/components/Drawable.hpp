/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <string>
#include "RaylibWrapper.hpp"

#include "Exceptions.hpp"

/*!
 \class Drawable
 \brief Component that is used on entities that can be rendered on the window.
*/
class Drawable {
    public:
        Drawable() {};

        Drawable(std::string spritePath) : spritePath(spritePath) {
            this->texture = LoadTexture(spritePath.c_str());
            if (!this->texture.id) {
                throw LoadAssetException("Failed to load asset: " + spritePath);
            }
        };

        Drawable(std::string spritePath, int resizeWidth, int resizeHeight) :
            spritePath(spritePath), resizeWidth(resizeWidth),
            resizeHeight(resizeHeight)
        {
            Image image = LoadImage(spritePath.c_str());
            ImageResizeNN(&image, resizeWidth, resizeHeight);
            this->texture = LoadTextureFromImage(image);
            UnloadImage(image);
            if (!this->texture.id) {
                throw LoadAssetException("Failed to load asset: " + spritePath);
            }
        };

        Drawable(Texture2D newTexture) : texture(newTexture) {
            if (!this->texture.id) {
                throw LoadAssetException("Failed to load texture");
            }
        };

        Drawable(
            std::string spritePath,
            int resizeWidth,
            int resizeHeight,
            bool isServer) :    spritePath(spritePath),
                                resizeWidth(resizeWidth),
                                resizeHeight(resizeHeight)
        {};

        Drawable(std::string spritePath, bool isServer) : spritePath(spritePath) {};

        std::string spritePath = "";
        int resizeWidth = -1;
        int resizeHeight = -1;

        Texture2D texture;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & spritePath;
            ar & resizeWidth;
            ar & resizeHeight;
        }

        friend class boost::serialization::access;

    protected:
    private:
};

#endif /* !DRAWABLE_HPP_ */

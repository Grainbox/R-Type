/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** AnimatedDraw
*/

#ifndef ANIMATEDDRAW_HPP_
#define ANIMATEDDRAW_HPP_

#include <string>
#include <vector>
#include <raylib.h>

#include "Exceptions.hpp"

/*!
 \class AnimatedDraw
 \brief Component that is used on entities that can be rendered and animated on the window with a spritesheet.
*/
class AnimatedDraw {
    public:
        AnimatedDraw(std::string spriteSheetPath, int nbCols, int nbRows) {
            Image spritesheet = LoadImage(spriteSheetPath.c_str());
            float frameWidth = spritesheet.width / nbCols;
            float frameHeight = spritesheet.height / nbRows;
            std::vector<Texture2D> list;

            for (int row = 0; row < nbRows; row++) {
                list.clear();
                for (int col = 0; col < nbCols; col++) {
                    Rectangle sourceRect = { col * frameWidth, row * frameHeight, frameWidth, frameHeight };
                    Image frameImage = ImageFromImage(spritesheet, sourceRect);
                    UnloadImage(frameImage);
                    list.push_back(LoadTextureFromImage(frameImage));
                }
                textureList.push_back(list);
            }
            for (auto list : textureList)
                for (auto texture : list)
                    if (!texture.id)
                        throw LoadAssetException("Failed to load asset: " + spriteSheetPath);
        }

        AnimatedDraw(std::string spriteSheetPath, int nbCols, int nbRows, int resizeWidth, int resizeHeight) {
            Image spritesheet = LoadImage(spriteSheetPath.c_str());
            float frameWidth = spritesheet.width / nbCols;
            float frameHeight = spritesheet.height / nbRows;
            std::vector<Texture2D> list;

            for (int row = 0; row < nbRows; row++) {
                list.clear();
                for (int col = 0; col < nbCols; col++) {
                    Rectangle sourceRect = { col * frameWidth, row * frameHeight, frameWidth, frameHeight };
                    Image frameImage = ImageFromImage(spritesheet, sourceRect);
                    ImageResizeNN(&frameImage, resizeWidth, resizeHeight);
                    UnloadImage(frameImage);
                    list.push_back(LoadTextureFromImage(frameImage));
                }
                textureList.push_back(list);
            }
            for (auto list : textureList)
                for (auto texture : list)
                    if (!texture.id)
                        throw LoadAssetException("Failed to load asset: " + spriteSheetPath);
        }

        std::vector<std::vector<Texture2D>> textureList;
    protected:
    private:
};

#endif /* !ANIMATEDDRAW_HPP_ */
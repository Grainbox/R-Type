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
#include "RaylibWrapper.hpp"

#include "Exceptions.hpp"

/*!
 \class AnimatedDraw
 \brief Component that is used on entities that can be rendered and animated on the window with a spritesheet.
*/
class AnimatedDraw {
    public:
        AnimatedDraw(std::string spriteSheetPath, int nbCols, int nbRows, float frameDuration = 0.1f, bool loop = true) : 
            _nbCols(nbCols), _nbRows(nbRows), _frameDuration(frameDuration), _loop(loop) {
            Image spritesheet = LoadImage(spriteSheetPath.c_str());
            float frameWidth = (float)spritesheet.width / nbCols;
            float frameHeight = (float)spritesheet.height / nbRows;
            std::vector<Texture2D> list;

            for (int row = 0; row < nbRows; row++) {
                list.clear();
                for (int col = 0; col < nbCols; col++) {
                    Rectangle sourceRect = { col * frameWidth, row * frameHeight, frameWidth, frameHeight };
                    Image frameImage = ImageFromImage(spritesheet, sourceRect);
                    list.push_back(LoadTextureFromImage(frameImage));
                    UnloadImage(frameImage);
                }
                textureList.push_back(list);
            }
            UnloadImage(spritesheet);
            for (auto list : textureList)
                for (auto texture : list)
                    if (!texture.id)
                        throw LoadAssetException("Failed to load asset: " + spriteSheetPath);
        }

        AnimatedDraw(std::string spriteSheetPath, int nbCols, int nbRows, int resizeWidth, int resizeHeight, float frameDuration = 0.1f, bool loop = true) :
            _nbCols(nbCols), _nbRows(nbRows), _frameDuration(frameDuration), _loop(loop) {
            Image spritesheet = LoadImage(spriteSheetPath.c_str());
            float frameWidth = (float)spritesheet.width / nbCols;
            float frameHeight = (float)spritesheet.height / nbRows;
            std::vector<Texture2D> list;

            for (int row = 0; row < nbRows; row++) {
                list.clear();
                for (int col = 0; col < nbCols; col++) {
                    Rectangle sourceRect = { col * frameWidth, row * frameHeight, frameWidth, frameHeight };
                    Image frameImage = ImageFromImage(spritesheet, sourceRect);
                    ImageResizeNN(&frameImage, resizeWidth, resizeHeight);
                    list.push_back(LoadTextureFromImage(frameImage));
                    UnloadImage(frameImage);
                }
                textureList.push_back(list);
            }
            UnloadImage(spritesheet);
            for (auto list : textureList)
                for (auto texture : list)
                    if (!texture.id)
                        throw LoadAssetException("Failed to load asset: " + spriteSheetPath);
        }

        std::vector<std::vector<Texture2D>> textureList;
        int _nbCols = 0;
        int _nbRows = 0;
        int currentFrame = 0;
        int currentRow = 0;
        float _frameDuration = 0.1f;
        float timeAccumulator = 0.0f;
        bool _loop = true;
    protected:
    private:
};

#endif /* !ANIMATEDDRAW_HPP_ */
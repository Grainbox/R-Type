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
#include "ResourceManager.hpp"

#include "Exceptions.hpp"

/*!
 \class AnimatedDraw
 \brief Component that is used on entities that can be rendered and animated on the window with a spritesheet.
*/
class AnimatedDraw {
    public:
        AnimatedDraw() {};

        AnimatedDraw(std::string spriteSheetPath, int nbCols, int nbRows, float frameDuration = 0.1f, bool loop = true) : 
            spritePath(spriteSheetPath), _nbCols(nbCols), _nbRows(nbRows), _frameDuration(frameDuration), _loop(loop) {
            textureList = ResourceManager::getInstance().getAnimatedTexture(spriteSheetPath, nbCols, nbRows);
            
            if (textureList.empty())
                throw LoadAssetException("Failed to load asset: " + spriteSheetPath);
        }

        AnimatedDraw(std::string spriteSheetPath, int nbCols, int nbRows, int resizeWidth, int resizeHeight, float frameDuration = 0.1f, bool loop = true) :
            _nbCols(nbCols), _nbRows(nbRows), _frameDuration(frameDuration), _loop(loop) {
            textureList = ResourceManager::getInstance().getAnimatedTexture(spriteSheetPath, nbCols, nbRows, resizeWidth, resizeHeight);
            
            if (textureList.empty())
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
        std::string spritePath = "";

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & spritePath;
            ar & _nbCols;
            ar & _nbRows;
            ar & _frameDuration;
            ar & _loop;
        }

        friend class boost::serialization::access;
    protected:
    private:
};

#endif /* !ANIMATEDDRAW_HPP_ */
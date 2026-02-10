/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** ResourceManager
*/

#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <unordered_map>
#include <string>
#include <iostream>
#include "RaylibWrapper.hpp"

/**
 * @class ResourceManager
 * @brief Singleton class for managing and caching game resources like textures.
 */
class ResourceManager {
public:
    /**
     * @brief Get the singleton instance of ResourceManager.
     * @return Reference to the ResourceManager instance.
     */
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }

    /**
     * @brief Load or retrieve a texture from the cache.
     * @param path Path to the texture file.
     * @param resizeWidth Optional resize width.
     * @param resizeHeight Optional resize height.
     * @return The loaded or cached Texture2D.
     */
    Texture2D getTexture(const std::string& path, int resizeWidth = -1, int resizeHeight = -1) {
        std::string key = path;
        if (resizeWidth != -1 && resizeHeight != -1) {
            key += "_" + std::to_string(resizeWidth) + "x" + std::to_string(resizeHeight);
        }

        if (_textures.find(key) != _textures.end()) {
            return _textures[key];
        }

        Texture2D texture;
        if (resizeWidth != -1 && resizeHeight != -1) {
            std::cout << "ResourceManager: Loading and resizing texture: " << path << " to " << resizeWidth << "x" << resizeHeight << std::endl;
            Image image = LoadImage(path.c_str());
            if (image.data != nullptr) {
                ImageResizeNN(&image, resizeWidth, resizeHeight);
                texture = LoadTextureFromImage(image);
                UnloadImage(image);
            }
        } else {
            std::cout << "ResourceManager: Loading texture: " << path << std::endl;
            texture = LoadTexture(path.c_str());
        }

        if (texture.id == 0) {
            std::cerr << "ResourceManager: Failed to load texture from " << path << std::endl;
        } else {
            _textures[key] = texture;
        }
        return texture;
    }

    /**
     * @brief Load or retrieve a list of textures (spritesheet) from the cache.
     * @param path Path to the spritesheet file.
     * @param nbCols Number of columns in the spritesheet.
     * @param nbRows Number of rows in the spritesheet.
     * @param resizeWidth Optional resize width for each frame.
     * @param resizeHeight Optional resize height for each frame.
     * @return The cached or loaded list of Texture2D frames.
     */
    std::vector<std::vector<Texture2D>> getAnimatedTexture(const std::string& path, int nbCols, int nbRows, int resizeWidth = -1, int resizeHeight = -1) {
        std::string key = path + "_" + std::to_string(nbCols) + "x" + std::to_string(nbRows) + "_" + std::to_string(resizeWidth) + "x" + std::to_string(resizeHeight);
        
        if (_animatedTextures.find(key) != _animatedTextures.end()) {
            return _animatedTextures[key];
        }

        std::cout << "ResourceManager: Loading animated texture: " << path << std::endl;
        Image spritesheet = LoadImage(path.c_str());
        if (spritesheet.data == nullptr) {
            std::cerr << "ResourceManager: Failed to load spritesheet from " << path << std::endl;
            return {};
        }

        float frameWidth = (float)spritesheet.width / nbCols;
        float frameHeight = (float)spritesheet.height / nbRows;
        std::vector<std::vector<Texture2D>> animatedList;

        for (int row = 0; row < nbRows; row++) {
            std::vector<Texture2D> list;
            for (int col = 0; col < nbCols; col++) {
                Rectangle sourceRect = { col * frameWidth, row * frameHeight, frameWidth, frameHeight };
                Image frameImage = ImageFromImage(spritesheet, sourceRect);
                if (resizeWidth != -1 && resizeHeight != -1) {
                    ImageResizeNN(&frameImage, resizeWidth, resizeHeight);
                }
                list.push_back(LoadTextureFromImage(frameImage));
                UnloadImage(frameImage);
            }
            animatedList.push_back(list);
        }
        UnloadImage(spritesheet);
        _animatedTextures[key] = animatedList;
        return animatedList;
    }

    /**
     * @brief Unload all cached textures and clear the cache.
     */
    void clear() {
        std::cout << "ResourceManager: Clearing cache..." << std::endl;
        for (auto& pair : _textures) {
            UnloadTexture(pair.second);
        }
        _textures.clear();

        for (auto& pair : _animatedTextures) {
            for (auto& row : pair.second) {
                for (auto& tex : row) {
                    UnloadTexture(tex);
                }
            }
        }
        _animatedTextures.clear();
    }

    // Disable copy and assignment
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    std::unordered_map<std::string, Texture2D> _textures;
    std::unordered_map<std::string, std::vector<std::vector<Texture2D>>> _animatedTextures;
};

#endif /* !RESOURCEMANAGER_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include <unordered_map>
#include <any>
#include <typeindex>
#include <memory>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

#include "Entity.hpp"

#include "Exceptions.hpp"

#include "Sparse_Array.hpp"

class Registry
{
public:

    Registry(std::string baseScene) : _currentScene(baseScene) {
        registerScene(baseScene);
    }

    template<typename Component>
    struct RemoveComponentWrapper {
        Registry* registry;

        RemoveComponentWrapper(Registry* reg) : registry(reg) {}

        void operator()(Entity ent, std::string scene) {
            registry->remove_component<Component>(ent, scene);
        }
    };

    template<typename Component>
    void remove_component(Entity ent, std::string scene) {
        Sparse_Array<Component> &components = getComponents<Component>(scene);

        components.erase(ent.getEntityId());
    }

    std::unordered_map<std::type_index, std::any> &registerScene(std::string sceneName) {
        if (_components_arrays.find(sceneName) == _components_arrays.end())
            _components_arrays[sceneName] = std::unordered_map<std::type_index, std::any>();
        return _components_arrays.at(sceneName);
    }

    template <typename Component>
    Sparse_Array<Component> &registerComponent(std::string scene)
    {
        std::type_index typeIndex(typeid(Component));

        if (_components_arrays.find(scene) == _components_arrays.end())
            registerScene(scene);

        auto &sceneComponents = _components_arrays.at(scene);

        if (sceneComponents.find(typeIndex) == sceneComponents.end()) {
            sceneComponents[typeIndex] = Sparse_Array<Component>();
            remove_components.push_back(RemoveComponentWrapper<Component>{this});
        }
        return std::any_cast<Sparse_Array<Component> &>(sceneComponents.at(typeIndex));
    }

    template <typename Component>
    Sparse_Array<Component> &getComponents(std::string scene)
    {
        std::type_index typeIndex(typeid(Component));

        if (_components_arrays.find(scene) == _components_arrays.end())
            registerScene(scene);

        auto &sceneComponents = _components_arrays.at(scene);

        if (sceneComponents.find(typeIndex) == sceneComponents.end())
            return registerComponent<Component>(scene);

        return std::any_cast<Sparse_Array<Component> &>(sceneComponents.at(typeIndex));
    }

    template <typename Component>
    Sparse_Array<Component> const &getComponents(std::string scene) const
    {
        std::type_index typeIndex(typeid(Component));

        if (_components_arrays.find(scene) == _components_arrays.end())
            throw SceneNotFoundException("Error: Registry::registerComponent -> Cannot find scene: " + scene);

        auto &sceneComponents = _components_arrays.at(scene);

        if (sceneComponents.find(typeIndex) == sceneComponents.end())
            throw ComponentTypeNotFoundException("Error: Registry::getComponents -> Cannot find component type");

        return std::any_cast<Sparse_Array<Component> const &>(sceneComponents.at(typeIndex));
    }

    template <typename Component>
    Component &addComponent(Entity ent, Component comp, std::string scene)
    {
        std::type_index typeIndex(typeid(Component));

        Sparse_Array<Component> &components = registerComponent<Component>(scene);

        return components.insert_at(ent.getEntityId(), comp).value();
    }

    template <typename Component>
    void removeComponent(Entity ent, std::string scene)
    {
        std::type_index typeIndex(typeid(Component));

        if (_components_arrays.find(scene) == _components_arrays.end())
            throw SceneNotFoundException("Error: Registry::registerComponent -> Cannot find scene: " + scene);

        auto &sceneComponents = _components_arrays.at(scene);

        if (sceneComponents.find(typeIndex) == sceneComponents.end())
            return;

        Sparse_Array<Component> &components = std::any_cast<Sparse_Array<Component> &>(sceneComponents.at(typeIndex));
        components.erase(ent.getEntityId());
    }

    Entity spawnEntity()
    {
        Entity newEntity;

        if (!deadEntities.empty()) {
            newEntity.setEntityId(deadEntities.front());
            deadEntities.pop_front();
        } else {
            newEntity.setEntityId(nextEntityId++);
        }

        return newEntity;
    }

    void killEntity(Entity const &ent, std::string scene)
    {
        try {
            for (auto &func : remove_components)
                func(ent, scene);
            deadEntities.push_front(ent.getEntityId());
        } catch (std::exception &e) {
            std::cerr << "Error: Registry::killEntity -> " << e.what() << std::endl;
        }
    }

    std::string getCurrentScene() {
        return this->_currentScene;
    }

    std::string setCurrentScene(std::string scene) {
        this->_currentScene = scene;
        return this->_currentScene;
    }

protected:
private:
    std::vector<std::function<void(Entity, std::string)>> remove_components;

    std::string _currentScene;

    std::unordered_map<std::string, std::unordered_map<std::type_index, std::any>> _components_arrays;

    std::list<size_t> deadEntities;
    size_t nextEntityId = 0;
};

#endif /* !REGISTRY_HPP_ */

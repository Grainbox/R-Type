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

    template<typename Component>
    struct RemoveComponentWrapper {
        Registry* registry;

        RemoveComponentWrapper(Registry* reg) : registry(reg) {}

        void operator()(Entity ent) {
            registry->remove_component<Component>(ent);
        }
    };

    template<typename Component>
    void remove_component(Entity ent) {
        Sparse_Array<Component> &components = getComponents<Component>();

        components.erase(ent.getEntityId());
    }

    template <typename Component>
    Sparse_Array<Component> &registerComponent()
    {
        std::type_index typeIndex(typeid(Component));

        if (_components_arrays.find(typeIndex) == _components_arrays.end()) {
            _components_arrays[typeIndex] = Sparse_Array<Component>();
            remove_components.push_back(RemoveComponentWrapper<Component>{this});
        }
        return std::any_cast<Sparse_Array<Component> &>(_components_arrays.at(typeIndex));
    }

    template <typename Component>
    Sparse_Array<Component> &getComponents()
    {
        std::type_index typeIndex(typeid(Component));

        if (_components_arrays.find(typeIndex) == _components_arrays.end())
            return registerComponent<Component>();
        return std::any_cast<Sparse_Array<Component> &>(_components_arrays.at(typeIndex));
    }

    template <typename Component>
    Sparse_Array<Component> const &getComponents() const
    {
        std::type_index typeIndex(typeid(Component));

        if (_components_arrays.find(typeIndex) == _components_arrays.end())
            throw ComponentTypeNotFoundException("Error: Registry::getComponents -> Cannot find component type");
        return std::any_cast<Sparse_Array<Component> const &>(_components_arrays.at(typeIndex));
    }

    template <typename Component>
    Component &addComponent(Entity ent, Component comp)
    {
        std::type_index typeIndex(typeid(Component));

        Sparse_Array<Component> &components = registerComponent<Component>();

        return components.insert_at(ent.getEntityId(), comp).value();
    }

    template <typename Component>
    void removeComponent(Entity ent)
    {
        std::type_index typeIndex(typeid(Component));

        if (_components_arrays.find(typeIndex) == _components_arrays.end())
            return;

        Sparse_Array<Component> &components = std::any_cast<Sparse_Array<Component> &>(_components_arrays.at(typeIndex));
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

    void killEntity(Entity const &ent)
    {
        try {
            for (auto &func : remove_components)
                func(ent);
            deadEntities.push_front(ent.getEntityId());
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

protected:
private:
    std::vector<std::function<void(Entity)>> remove_components;
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::list<size_t> deadEntities;
    size_t nextEntityId = 0;
};

#endif /* !REGISTRY_HPP_ */

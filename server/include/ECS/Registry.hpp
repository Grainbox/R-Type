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

#include "components/Drawable.hpp"
#include "components/Velocity.hpp"
#include "components/Position.hpp"

#include "Entity.hpp"
#include "Exceptions.hpp"

class Registry
{
public:
    template <typename ComponentType>
    std::vector<std::reference_wrapper<ComponentType>> registerComponent()
    {
        std::type_index typeIndex(typeid(ComponentType));

        auto it = componentArrays.find(typeIndex);

        if (it == componentArrays.end())
        {
            componentArrays.emplace(typeIndex, std::vector<std::pair<Entity, ComponentType>>());
        }
        return getComponents<ComponentType>();
    }

    template <typename ComponentType>
    std::vector<std::reference_wrapper<ComponentType>> getComponents()
    {
        std::type_index typeIndex(typeid(ComponentType));
        auto it = componentArrays.find(typeIndex);

        if (it == componentArrays.end())
        {
            throw ComponentNotFoundException("Component array not found for the given type");
        }

        std::vector<std::pair<Entity, ComponentType>> &components = std::any_cast<std::vector<std::pair<Entity, ComponentType>> &>(it->second);
        std::vector<std::reference_wrapper<ComponentType>> result;

        for (auto &componentPair : components)
        {
            result.push_back(std::ref(componentPair.second));
        }

        return result;
    }

    template <typename ComponentType>
    std::vector<std::reference_wrapper<ComponentType>> const getComponents() const
    {
        std::type_index typeIndex(typeid(ComponentType));
        auto it = componentArrays.find(typeIndex);

        if (it == componentArrays.end())
        {
            throw ComponentNotFoundException("Component array not found for the given type");
        }

        std::vector<std::pair<Entity, ComponentType>> &components = std::any_cast<std::vector<std::pair<Entity, ComponentType>> &>(it->second);
        std::vector<std::reference_wrapper<ComponentType>> result;

        for (auto &componentPair : components)
        {
            result.push_back(std::ref(componentPair.second));
        }

        return result;
    }

    template <typename ComponentType>
    ComponentType &addComponent(Entity ent, ComponentType comp)
    {
        std::type_index typeIndex(typeid(ComponentType));

        auto it = componentArrays.find(typeIndex);

        if (it == componentArrays.end())
        {
            it = componentArrays.emplace(typeIndex, std::vector<std::pair<Entity, ComponentType>>()).first;
        }

        std::vector<std::pair<Entity, ComponentType>> &components = std::any_cast<std::vector<std::pair<Entity, ComponentType>> &>(it->second);
        components.emplace_back(ent, std::move(comp));

        return components.back().second;
    }

    template <typename ComponentType>
    void removeComponent(Entity ent)
    {
        std::type_index typeIndex(typeid(ComponentType));

        auto it = componentArrays.find(typeIndex);

        if (it != componentArrays.end())
        {
            std::vector<std::pair<Entity, ComponentType>> &components = std::any_cast<std::vector<std::pair<Entity, ComponentType>> &>(it->second);

            auto compIt = std::find_if(components.begin(), components.end(),
                                       [ent](const std::pair<Entity, ComponentType> &componentPair)
                                       {
                                           return componentPair.first == ent;
                                       });

            if (compIt != components.end())
            {
                components.erase(compIt);
            }
        }
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
            removeComponent<Position>(ent);
            removeComponent<Velocity>(ent);
            removeComponent<Drawable>(ent);
            deadEntities.push_front(ent.getEntityId());
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

protected:
private:
    std::unordered_map<std::type_index, std::any> componentArrays;
    std::list<size_t> deadEntities;
    size_t nextEntityId = 1;
};

#endif /* !REGISTRY_HPP_ */

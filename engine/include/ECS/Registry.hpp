/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include <unordered_map>
#include <map>
#include <any>
#include <typeindex>
#include <memory>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <raylib.h>
#include <boost/optional.hpp>

#include <asio.hpp>

#include "Entity.hpp"

#include "Exceptions.hpp"

#include "Sparse_Array.hpp"

#include "Communication_Headers.hpp"

/*!
 \class Registry
 \brief Class responsible for managing entities and their components.

 The Registry class is used to handle entities, their components, and interactions between them within different scenes. It offers functionalities for adding, removing, and querying components and entities.
*/
class Registry
{
public:

    /*!
     \brief Constructor for Registry.
     \param baseScene The name of the base scene to register.
    */
    Registry(std::string baseScene) : _currentScene(baseScene) {
        registerScene(baseScene);
    }

    /*!
     \brief Wrapper struct to remove a component from an entity.
     \tparam Component The type of component to remove.
    */
    template<typename Component>
    struct RemoveComponentWrapper {
        Registry* registry;

        RemoveComponentWrapper(Registry* reg) : registry(reg) {}

        void operator()(Entity ent, std::string scene) {
            registry->remove_component<Component>(ent, scene);
        }
    };

    /*!
     \brief Removes a component from an entity.
     \tparam Component The type of component to remove.
     \param ent The entity from which to remove the component.
     \param scene The scene in which the entity resides.
    */
    template<typename Component>
    void remove_component(Entity ent, std::string scene) {
        Sparse_Array<Component> &components = getComponents<Component>(scene);

        components.erase(ent.getEntityId());
    }

    /*!
     \brief Registers a scene to the registry.
     \param sceneName The name of the scene to register.
     \return A reference to the scene's component storage.
    */
    std::unordered_map<std::type_index, std::any> &registerScene(std::string sceneName) {
        if (_components_arrays.find(sceneName) == _components_arrays.end()) {
            _components_arrays[sceneName] = std::unordered_map<std::type_index, std::any>();
            nextEntityId[sceneName] = 0;
        }
        return _components_arrays.at(sceneName);
    }

    /*!
     \brief Registers a component type to a scene.
     \tparam Component The type of component to register.
     \param scene The scene in which to register the component.
     \return A reference to the sparse array of the registered component.
    */
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

    /*!
     \brief Retrieves the components of a specific type in a given scene.
     \tparam Component The type of component to retrieve.
     \param scene The scene from which to retrieve the components.
     \return A reference to the sparse array of the requested component type.
    */
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

    /*!
     \brief Retrieves the components of a specific type in a given scene (const version).
     \tparam Component The type of component to retrieve.
     \param scene The scene from which to retrieve the components.
     \return A const reference to the sparse array of the requested component type.
    */
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

    /*!
     \brief Adds a component to an entity in a given scene.
     \tparam Component The type of component to add.
     \param ent The entity to which the component will be added.
     \param comp The component to add to the entity.
     \param scene The scene in which the entity resides.
     \return A reference to the added component.
    */
    template <typename Component>
    Component &addComponent(Entity ent, Component comp, std::string scene)
    {
        std::type_index typeIndex(typeid(Component));

        Sparse_Array<Component> &components = registerComponent<Component>(scene);

        return components.insert_at(ent.getEntityId(), comp).value();
    }

    /*!
     \brief Removes a component from an entity in a given scene.
     \tparam Component The type of component to remove.
     \param ent The entity from which the component will be removed.
     \param scene The scene in which the entity resides.
    */
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

    /*!
     \brief Spawns a new entity and returns it.
     \return The newly spawned entity.
    */
    Entity spawnEntity(std::string scene)
    {
        Entity newEntity;

        registerScene(scene);

        if (!deadEntities[scene].empty()) {
            newEntity.setEntityId(deadEntities[scene].front());
            deadEntities[scene].pop_front();
        } else {
            newEntity.setEntityId(nextEntityId[scene]++);
        }

        return newEntity;
    }

    /*!
     \brief Kills an entity and removes all its components in a given scene.
     \param ent The entity to kill.
     \param scene The scene in which the entity resides.
    */
    void killEntity(Entity const &ent, std::string scene)
    {
        try {
            for (auto &func : remove_components)
                func(ent, scene);
            deadEntities[scene].push_front(ent.getEntityId());
        } catch (std::exception &e) {
            std::cerr << "Error: Registry::killEntity -> " << e.what() << std::endl;
        }
    }

    /*!
     \brief Gets the current active scene.
     \return The name of the current scene.
    */
    std::string getCurrentScene() {
        return this->_currentScene;
    }

    /*!
     \brief Sets the current active scene.
     \param scene The name of the scene to set as active.
     \return The name of the new current scene.
    */
    std::string setCurrentScene(std::string scene) {
        this->_currentScene = scene;
        return this->_currentScene;
    }

    // /*!
    // \brief Retrieve Entity Component
    // \tparam The component type
    // \param entity_id the entity id
    // */
    // template <typename Component>
    // std::optional<Component &>get_entity_component(size_t entity_id)
    // {
    //     auto &comps = getComponents<Component>(this->getCurrentScene());

    //     if (entity_id >= comps.size())
    //         return {};
    //     if (comps[entity_id].has_value()) {
    //         // return comps[entity_id];
    //         return std::ref(comps[entity_id].value());
    //     } else {
    //         return {};
    //     }
    // }

    /*!
    \brief Retrieve Entity Component for boost

    \tparam The component type

    \param entity_id the entity id
    */
    template <typename Component>
    boost::optional<Component>get_boost_entity_component(size_t entity_id)
    {
        auto &comps = getComponents<Component>(this->getCurrentScene());

        if (entity_id >= comps.size())
            return boost::none;
        if (comps[entity_id].has_value()) {
            return boost::optional<Component>(*comps[entity_id]);
        } else {
            return boost::none;
        }
    }

    size_t getNextEntityId()
    {
        return this->nextEntityId.at(this->getCurrentScene());
    }

    std::list<size_t> getDeadEntities()
    {
        registerScene(this->getCurrentScene());
        return this->deadEntities[this->getCurrentScene()];
    }

    /*!
    \brief Store the given function in the event scripts array

    \param func the function to store
    \return the event script id
    */
    size_t registerEventScript(std::function<void(Registry &, size_t,
        asio::ip::udp::socket &_udp_socket,
        asio::ip::udp::endpoint &_server_endpoint)> func)
    {
        event_scripts.push_back(func);
        return event_scripts.size() - 1;
    }

    /*!
    \brief Get the event script for the given id

    \param id The id of the script
    \return The event script
    */
    std::function<void(Registry &, size_t, asio::ip::udp::socket &_udp_socket,
        asio::ip::udp::endpoint &_server_endpoint)> getEventScript(size_t id)
    {
        if (id >= event_scripts.size())
            throw (ScriptNotFoundException("Script not found for id: " + id));
        return event_scripts.at(id);
    }

    /*!
    \brief Store the given function in the communication scripts array

    \param func the function to store
    \return the communication script id
    */
    size_t registerComScript(std::function<void(Registry &, size_t, MessageHandlerData)> func)
    {
        com_scripts.push_back(func);
        return com_scripts.size() - 1;
    }

    /*!
    \brief Get the communication script for the given id

    \param id The id of the communication script
    \return The communication script id
    */
    std::function<void(Registry &, size_t, MessageHandlerData)> getComScript(size_t id)
    {
        if (id >= com_scripts.size())
            throw (ScriptNotFoundException("Script not found for id: " + id));
        return com_scripts.at(id);
    }

protected:
private:
    std::vector<std::function<void(Entity, std::string)>> remove_components; ///< Functions for removing components from entities.
    std::string _currentScene; ///< Name of the current active scene.
    std::unordered_map<std::string, std::unordered_map<std::type_index, std::any>> _components_arrays; ///< Storage for components in each scene.
    std::map<std::string, size_t> nextEntityId; ///< ID to be assigned to the next spawned entity.
    std::map<std::string, std::list<size_t>> deadEntities; ///< List of IDs of entities that have been destroyed.

    std::vector<std::function<void(Registry &, size_t, asio::ip::udp::socket &_udp_socket,
        asio::ip::udp::endpoint &_server_endpoint)>> event_scripts; ///< List of event scripts defined by the client.
    std::vector<std::function<void(Registry &, size_t, MessageHandlerData)>> com_scripts; ///< List of communication scripts defined by the user
};

#endif /* !REGISTRY_HPP_ */

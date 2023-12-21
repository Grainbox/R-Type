# Creating the UDP Entity for Message Reception

## Overview
This documentation outlines the steps to create an entity in your main function (outside of the engine) that handles UDP message receptions using the `ReceiveUDP` component.

## Step 1: Creating the UDP Entity
In your main function, spawn a new UDP entity like this:

```cpp
Entity udp = r.spawnEntity("mainMenu");
```

## Step 2: Creating the Script Function
Define a script function that will handle the incoming UDP messages. Below is an example function named `create_game_handler`:

```cpp
std::string create_game_handler(Registry &r, size_t entity_id, std::string message, MessageType type)
{
    std::cout << "Create Game" << std::endl;

    if (type != MessageType::ECS_Transfert) {
        return "";
    }

    std::istringstream archive_stream(message);
    boost::archive::text_iarchive archive(archive_stream);
    TransfertECSMessage msg;
    archive >> msg;
    msg.header.type = MessageType::ECS_Transfert;

    std::list<size_t> deadEntities = r.getDeadEntities();

    for (size_t i = 0; i < r.getNextEntityId(); i++) {
        auto it = std::find(deadEntities.begin(), deadEntities.end(), i);

        if (!deadEntities.empty() && it == deadEntities.end())
            continue;

        EntityComponents comps;

        comps.entity_id = i;
        // comps.clickable = r.get_entity_component<Clickable>(i);
        comps.controllable = r.get_boost_entity_component<Controllable>(i);
        comps.drawable = r.get_boost_entity_component<Drawable>(i);
        // comps.hitbox = r.get_entity_component<Hitbox>(i);
        // comps.kb_input = r.get_entity_component<KeyboardInput>(i);
        comps.position = r.get_boost_entity_component<Position>(i);
        // comps.react_cursor = r.get_entity_component<ReactCursor>(i);
        comps.velocity = r.get_boost_entity_component<Velocity>(i);
        msg.entities.push_back(comps);
    }

    std::ostringstream new_archive_stream;
    boost::archive::text_oarchive new_archive(new_archive_stream);
    new_archive << msg;

    std::string serialized_str = archive_stream.str();

    std::cout << "Sending: " << serialized_str << std::endl;

    return serialized_str;
}
```

## Step 3: Creating and Registering `ReceiveUDP` Component
Create the `ReceiveUDP` component and register your script function with it. Pass the script ID to the `ReceiveUDP` constructor.

```cpp
ReceiveUDP receiveUDP(r.registerComScript(std::bind(create_game_handler,
                std::placeholders::_1,
                std::placeholders::_2,
                std::placeholders::_3,
                std::placeholders::_4))
        );
```

## Step 4: Addinf your component to your entity
```cpp
r.addComponent<ReceiveUDP>(udp, receiveUDP, "mainMenu");
```

## Usage
Your script will be called every time a UDP message is received. Ensure that the `ReceiveUDP` component is properly integrated with your entity-component system for effective handling of the messages.

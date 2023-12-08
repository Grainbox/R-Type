# Scene Initialization for Your Game

To initialize scenes in a game, it's necessary to follow several key steps. This guide provides a detailed explanation of each step.

## Step 1: Creating the `Registry` Object

First, create an object of the `Registry` class. This object serves as a container for all entities and components in each scene.

```cpp
Registry r("mainMenu");
```

In this example, the base scene (or the first scene of the game) is named `"mainMenu"`.

## Step 2: Adding Entities and Components

Once the `Registry` object is created, you need to add entities and components for each scene.

### Creating and Adding Entities

For each entity, use the `spawnEntity()` method of the `Registry` object:

```cpp
Entity player = r.spawnEntity();
Entity button = r.spawnEntity();
// and so on for other entities
```

### Adding Components to Entities

For each entity, add the necessary components. For example, to add a position, a graphic element (drawable), control capability, and velocity to the `player` entity in the `"mainMenu"` scene:

```cpp
Position pos(100, 0);
Drawable draw("assets/entity_1.png");
Controllable control;
Velocity vel(0, 0);

r.addComponent<Position>(player, pos, "mainMenu");
r.addComponent<Drawable>(player, draw, "mainMenu");
r.addComponent<Controllable>(player, control, "mainMenu");
r.addComponent<Velocity>(player, vel, "mainMenu");
```

Repeat this process for all the necessary entities and components.

## Step 3: Setup the Engine Config:

Here is the EngineConfig class:
```cpp
struct EngineConfig {
    bool isServer;
    Registry *r;
};
```

You should setup an object of it with your configuration: is the engine running as a server or as a client, a pointer to your registry, etc...

```cpp
EngineConfig config = {true, &r};
```

## Step 3: Launching the Game with the `Registry` Object

Finally, pass the `EngineConfig` object to the `Game` class to start the game with the defined configuration:

```cpp
Game game(config);
game.run();
```

In this example, the `Game` object is initialized with the address of the `Registry` object, and the `run()` method is called to launch the game.

## Complete Example

Here is a complete example showing the definition of two scenes (`mainMenu` and `game`) and launching the game with this configuration:

```cpp
// Initialization of the Registry object with the first scene
Registry r("mainMenu");

// Adding entities and components for the "mainMenu" scene
Entity player = r.spawnEntity();
// ...adding components for player...

Entity button = r.spawnEntity();
// ...adding components for button...

// Adding entities and components for the "game" scene
Entity player2 = r.spawnEntity();
// ...adding components for player2...

// Initializing and launching the game
Game game(&r);
game.run();
```

By following these steps, you can initialize and configure the scenes for your game in C++.

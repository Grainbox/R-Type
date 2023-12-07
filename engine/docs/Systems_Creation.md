# Creating and Adding Custom Systems in the Engine

## Steps to Create a New System

### Step 1: Define the System's Function

Begin by clearly defining the function of your system. For example, a `health` system might manage the health of game characters.

### Step 2: Access Necessary Components

Use the `Registry` class to access the components your system needs. For example, if your system manages health, it might need access to a `Health` component.

```cpp
Sparse_Array<Health> &healthComponents = r.getComponents<Health>(scene);
```

### Step 3: Implement the System Logic

Implement the logic of the system based on the accessible components. For example, a health system may reduce a character's health when they take damage.

```cpp
void health_system(Registry &r) {
    std::string scene = r.getCurrentScene();
    Sparse_Array<Health> &healthComponents = r.getComponents<Health>(scene);

    // System logic
    for (size_t i = 0; i < healthComponents.size(); ++i) {
        auto &health = healthComponents[i];

        if (!health)
            continue;

        // Modify health based on game logic
        // Example: health.value().hp -= damage;
    }
}
```

## Tips for Creating Systems

- **Modularity:** Each system should be responsible for a single task or aspect of the game.
- **Component Access:** Use the `Registry` class to access the components necessary for your system.
- **Performance:** Optimize performance by avoiding unnecessary loops or computations.
- **Scalability:** Ensure your system can be easily extended or modified.

## Integrating the System into the Game

Once your system is implemented, integrate it into the main game loop. For example, if you have a `health` system, you might call it at each frame update.

```cpp
while (game.isRunning()) {
    // ...
    health_system(registry);
    // ...
}
```

By following these steps and drawing inspiration from existing examples, you can effectively create and integrate your own custom system into a game.

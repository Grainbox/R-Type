# Utilisation de la Classe Registry

La classe `Registry` est conçue pour gérer les entités et les composants dans un moteur de jeu ECS. Voici comment vous pouvez l'utiliser dans votre projet.

## Créer une Entité

Pour créer une nouvelle entité :

```cpp
Registry registry;
Entity newEntity = registry.spawnEntity();
```

## Créer un Composant

La création d'un composant dépend de la définition de votre composant. Par exemple, si vous avez un composant `Transform` :

```cpp
struct Transform {
    float x, y, z;
};
```

## Ajouter un Composant à une Entité

Pour ajouter un composant à une entité :

```cpp
Transform transform = {0.0f, 0.0f, 0.0f};
registry.addComponent<Transform>(newEntity, transform);
```

## Retirer un Composant d'une Entité

Pour retirer un composant d'une entité :

```cpp
registry.removeComponent<Transform>(newEntity);
```

## Récupérer tous les Composants d'un Certain Type

Pour récupérer tous les composants d'un certain type :

```cpp
auto &components = registry.getComponents<Transform>();
```

## Modifier la Valeur des Composants

Pour modifier la valeur d'un composant spécifique :

```cpp
auto &velocity = this->r.getComponents<Velocity>();

for (size_t i = 0; i < velocity.size(); ++i)
{
    auto &vel = velocity[i];

    if (!vel)
        continue;

    vel.value().vx = 0;
    vel.value().vy = 0;
}
```

## Supprimer une Entité et ses Composants

La méthode `killEntity` est utilisée pour supprimer une entité et tous ses composants associés. Elle gère également les exceptions pour assurer une exécution sûre.

```cpp
void killEntity(Entity const &ent) {
    try {
        removeComponent<Position>(ent);
        removeComponent<Velocity>(ent);
        // Ajouter ici la suppression des autres composants si nécessaire
        deadEntities.push_front(ent.getEntityId());
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
```

## Gestion des Composants lors de l'Ajout d'un Nouveau Composant

Lorsque vous ajoutez un composant à une entité, il est important de s'assurer que la méthode `killEntity` soit mise à jour pour gérer également ce nouveau type de composant. Par exemple, si vous ajoutez un composant `Health`, assurez-vous d'ajouter la ligne `removeComponent<Health>(ent);` dans la méthode `killEntity`. Cela garantit que tous les composants sont correctement nettoyés lors de la suppression d'une entité.

```cpp
void killEntity(Entity const &ent) {
    try {
        removeComponent<Position>(ent);
        removeComponent<Velocity>(ent);
        removeComponent<Health>(ent);  // Ligne ajoutée pour le nouveau composant
        // ...
        deadEntities.push_front(ent.getEntityId());
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
```

## Notes

- Assurez-vous de gérer les exceptions potentielles, en particulier lorsque vous travaillez avec `getComponents`.
- Les modifications apportées aux composants sont directement réfléchies dans le `Registry`, car les composants sont référencés.

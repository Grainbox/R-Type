# Création et Ajout de Systèmes Personnalisés dans l'Engine

## Étapes pour Créer un Nouveau Système

### Étape 1: Définir la Fonction du Système

Commencez par définir clairement la fonction de votre système. Par exemple, un système de `health` pourrait gérer la santé des personnages du jeu.

### Étape 2: Accéder aux Composants Nécessaires

Utilisez la classe `Registry` pour accéder aux composants dont votre système a besoin. Par exemple, si votre système gère la santé, il pourrait nécessiter l'accès à un composant `Health`.

```cpp
Sparse_Array<Health> &healthComponents = r.getComponents<Health>(scene);
```

### Étape 3: Implémenter la Logique du Système

Implémentez la logique du système en fonction des composants accessibles. Par exemple, un système de santé peut réduire la santé d'un personnage lorsqu'il subit des dégâts.

```cpp
void health_system(Registry &r) {
    std::string scene = r.getCurrentScene();
    Sparse_Array<Health> &healthComponents = r.getComponents<Health>(scene);

    // Logique du système
    for (size_t i = 0; i < healthComponents.size(); ++i) {
        auto &health = healthComponents[i];

        if (!health)
            continue;

        // Modifier la santé en fonction de la logique du jeu
        // Exemple : health.value().hp -= damage;
    }
}
```

## Conseils pour la Création de Systèmes

- **Modularité :** Chaque système doit être responsable d'une seule tâche ou aspect du jeu.
- **Accès aux Composants :** Utilisez la classe `Registry` pour accéder aux composants nécessaires à votre système.
- **Performance :** Optimisez la performance en évitant des boucles ou des calculs inutiles.
- **Scalabilité :** Assurez-vous que votre système peut facilement être étendu ou modifié.

## Intégration du Système dans le Jeu

Une fois votre système implémenté, intégrez-le dans la boucle principale du jeu. Par exemple, si vous avez un système de `health`, vous pourriez l'appeler à chaque mise à jour de la frame.

```cpp
while (game.isRunning()) {
    // ...
    health_system(registry);
    // ...
}
```

En suivant ces étapes et en vous inspirant des exemples existants, vous pouvez créer et intégrer efficacement votre propre système personnalisé dans un jeu.

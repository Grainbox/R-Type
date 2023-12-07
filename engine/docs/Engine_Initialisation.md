# Initialisation des Scènes pour votre jeu

Pour initialiser les scènes dans un jeu, il est nécessaire de suivre plusieurs étapes clés. Ce guide fournit une explication détaillée de chaque étape.

## Étape 1: Création de l'Objet `Registry`

Tout d'abord, il faut créer un objet de la classe `Registry`. Cet objet sert de conteneur pour toutes les entités et composants de chaque scène.

```cpp
Registry r("mainMenu");
```

Dans cet exemple, la scène de base (ou la première scène du jeu) est nommée `"mainMenu"`.

## Étape 2: Ajout des Entités et Composants

Une fois l'objet `Registry` créé, il faut ajouter les entités et les composants pour chaque scène.

### Création et Ajout d'Entités

Pour chaque entité, utilisez la méthode `spawnEntity()` de l'objet `Registry` :

```cpp
Entity player = r.spawnEntity();
Entity button = r.spawnEntity();
// et ainsi de suite pour d'autres entités
```

### Ajout de Composants aux Entités

Pour chaque entité, ajoutez les composants nécessaires. Par exemple, pour ajouter une position, un élément graphique (drawable), une capacité de contrôle et une vélocité à l'entité `player` dans la scène `"mainMenu"` :

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

Répétez ce processus pour toutes les entités et tous les composants nécessaires.

## Étape 3: Lancement du Jeu avec l'Objet `Registry`

Enfin, passez l'objet `Registry` à la classe `Game` pour démarrer le jeu avec la configuration définie :

```cpp
Game game(&r);
game.run();
```

Dans cet exemple, l'objet `Game` est initialisé avec l'adresse de l'objet `Registry`, et la méthode `run()` est appelée pour lancer le jeu.

## Exemple Complet

Voici un exemple complet montrant la définition de deux scènes (`mainMenu` et `game`) et le lancement du jeu avec cette configuration :

```cpp
// Initialisation de l'objet Registry avec la première scène
Registry r("mainMenu");

// Ajout des entités et composants pour la scène "mainMenu"
Entity player = r.spawnEntity();
// ...ajout des composants pour player...

Entity button = r.spawnEntity();
// ...ajout des composants pour button...

// Ajout des entités et composants pour la scène "game"
Entity player2 = r.spawnEntity();
// ...ajout des composants pour player2...

// Initialisation et lancement du jeu
Game game(&r);
game.run();
```

En suivant ces étapes, vous pouvez initialiser et configurer les scènes de votre jeu en C++.

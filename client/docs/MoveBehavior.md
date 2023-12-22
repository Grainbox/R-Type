>Définies les comportement de l'entity vis a vis de ses mouvements

[MoveBehavior.hpp](../../engine/include/components/MoveBehavior.hpp)

##### Crée un Composant

```C++
MoveBehavior behavior;

##### Paramétrage d'un comportement

```C++
behavior.setOffScreenMov(false); // exemple de comportement qui empêchera l'entité de sortir de l'écran durant ses déplacements.

r.addComponent<MoveBehavior>(player, behavior, "mainMenu");
```

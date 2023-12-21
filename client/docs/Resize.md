>Définie une modification de taille sur l'entity

[Position.hpp](../../engine/include/components/Resize.hpp)

##### Crée un Composant

```C++
Resize rs(100, 100); // (rx, ry)

r.addComponent<Resize>(player, rs, "mainMenu");
```
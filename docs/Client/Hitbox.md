>Définies une Hitbox sur l'entity

[Hitbox.hpp](../../engine/include/components/Hitbox.hpp)

##### Crée un Composant

```C++
Hitbox box(100, 100);
Hitbox box(100, 100, true); // active l'affichage de la hitbox

r.addComponent<Hitbox>(player, box, "mainMenu");
```

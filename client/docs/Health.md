>Définies la vie d'une entitée

[Health.hpp](../../engine/include/components/Health.hpp)

##### Crée un Composant

```C++
Health life(100);
Health life(); // default 100

r.addComponent<Health>(player, life, "Game");
```

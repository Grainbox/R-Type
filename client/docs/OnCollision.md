>Définies une Hitbox sur l'entity

[OnCollision.hpp](../../engine/include/components/OnCollision.hpp)

##### Crée un Composant

```C++
OnCollision onHit;
onHit.addReaction(HitTag::hitTag tag, size_t script_id); // Ajout d'une réaction. La fonction référencé par script_id sera proc lorsqu'une collision avec une entité possédant le hitTag précisé a lieu.

r.addComponent<OnCollision>(player, onHit, "mainMenu");
```

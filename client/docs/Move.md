>Définies une Hitbox sur l'entity

[Move.hpp](../../engine/include/components/Move.hpp)

> Composant inutile pour le moment car velocity et position font deja la meme chose

##### Crée un Composant MoveLeft

```C++
MoveLeft mf;

r.addComponent<MoveLeft>(box, mf, "GameView");
```

##### Crée un Composant MoveRight

```C++
MoveRight mr;

r.addComponent<MoveRight>(box, mr, "GameView");
```

##### Crée un Composant MoveUp

```C++
MoveUp mf;

r.addComponent<MoveUp>(box, mu, "GameView");
```

##### Crée un Composant MoveDown

```C++
MoveDown mf;

r.addComponent<MoveDown>(box, md, "GameView");
```

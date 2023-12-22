> Permet de jouer de la musique

[SoundWrapper.hpp](../../engine/include/components/SoundWrapper.hpp)

##### Crée un Composant

> Pas Fonctionnel pour le moment.

```C++
Entity boombox = r->spawnEntity();

SoundWrapper soundbox("assets/musique.wav", true); // si true, la musique ce lance directement
SoundWrapper soundbox("assets/musique.wav", false);
SoundWrapper soundbox("assets/musique.wav"); // default false

r->addComponent<SoundWrapper>(boombox, soundbox, "MaView");
```

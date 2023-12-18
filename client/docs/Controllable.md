> Permet le déplacement d'une entity

[Controllable.hpp](../../engine/include/components/Controllable.hpp)

##### Crée un Composant

```C++
Controllable control;

r.addComponent<Controllable>(player, control, "MyView");
```

##### Définir une touche :

```C++
control.setKeyboardKey(&control.Up, KEY_UP); // Monter
control.setKeyboardKey(&control.Down, KEY_DOWN); // Descendre
control.setKeyboardKey(&control.Left, KEY_LEFT); // Gauche
control.setKeyboardKey(&control.Right, KEY_RIGHT); // Droite
```


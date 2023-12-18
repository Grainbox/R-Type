> Permet le déplacement d'une entity

[Controllable.hpp](../../engine/include/components/Controllable.hpp)

##### Crée un Composant

```C++
Controllable control;

r.addComponent<Controllable>(player, control, "MyView");
```

##### Définir une touche :

```C++
control.setKeyboardKey(&control.Up, sf::Keyboard::Up); // Monter
control.setKeyboardKey(&control.Down, sf::Keyboard::Down); // Descendre
control.setKeyboardKey(&control.Left, sf::Keyboard::Left); // Gauche
control.setKeyboardKey(&control.Right, sf::Keyboard::Right); // Droite
```


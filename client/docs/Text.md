> Crée un text

[Text.hpp](../../engine/include/components/Text.hpp)

##### Crée un Composant

```C++
Text txt("Hello world"); // affiche "Hello world" en couleur noir, et en taille 20
Text txt("Hello world", RED); // affiche "Hello world" en couleur ROUGE, et en taille 20
Text txt("Hello world", 30); // affiche "Hello world" en couleur noir, et en taille 30
Text txt("Hello world", RED, 60); // affiche "Hello world" en couleur rouge, et en taille 60

r.addComponent<Text>(player, txt, "Game");
```

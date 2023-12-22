> Permet de définir un évènement qui sera proc si une certaine touche est appuyée

[KeyReaction.hpp](../../engine/include/components/KeyReaction.hpp)

##### Crée un Composant

```C++
// Fonction de test

void debug ()
{
	std::cout << "hello world" << std::endl;
}

Kreaction KReact(debug);

```

```C++
// Exemple dans une class view, avec appuie sur la touche 'A'.

void MaClass::debug ()
{
	std::cout << "hello world" << std::endl;
}

KeyReaction KReactDebug(KEY_A, std::bind(&MaClass::debug, this, std::placeholders::_1));

```
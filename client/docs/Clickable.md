> Permet de définir un évènement qui sera proc si cliqué

[Clickable.hpp](../../engine/include/components/Clickable.hpp)

⚠️ nécessite une Hitbox pour fonctionner

##### Crée un Composant

```C++
// Fonction de test

void debug ()
{
	std::cout << "hello world" << std::endl;
}

Clickable click(debug);

```

```C++
// Exemple dans une class view

void MaClass::debug ()
{
	std::cout << "hello world" << std::endl;
}

Clickable clickDebug(std::bind(&MaClass::debug, this, std::placeholders::_1));

```


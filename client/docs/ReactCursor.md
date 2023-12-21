> Permet de définir un évènement qui sera proc si le curseur de la souris passe sur l'entité

[ReactCursor.hpp](../../engine/include/components/ReactCursor.hpp)

⚠️ nécessite une Hitbox pour fonctionner

##### Crée un Composant

```C++
// Fonction de test

void debug ()
{
	std::cout << "hello world" << std::endl;
}

ReactCursor reactC(debug);

```

```C++
// Exemple dans une class view

void MaClass::debug ()
{
	std::cout << "hello world" << std::endl;
}

ReactCursor clickDebug(std::bind(&MaClass::debug, this, std::placeholders::_1));

```


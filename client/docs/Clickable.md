# Documentation pour l'Intégration de Scripts Clickables

Cette documentation explique comment ajouter un script personnalisé et l'exécuter lors d'un clic dans le cadre de notre système ECS (Entity-Component-System).

## Ajout d'un Nouveau Script

### Étape 1: Définir le Script
Tout d'abord, définissez votre script. Le script doit être une fonction respectant la signature suivante :

```cpp
void nomDuScript(Registry &r, size_t entity_id, asio::ip::udp::socket &_udp_socket, asio::ip::udp::endpoint &_server_endpoint)
{
    // Logique du script
}
```

### Étape 2: Enregistrer le Script
Enregistrez votre script en utilisant la méthode `registerScript`. Par exemple :

```cpp
size_t scriptID = r->registerScript(nomDuScript);
```

## Création d'un Composant Clickable

### Étape 1: Créer une Instance de Clickable
Créez une instance du composant `Clickable` en passant l'ID du script :

```cpp
Clickable clickComponent(scriptID);
```

### Étape 2: Attacher le Composant à une Entité
Attachez `clickComponent` à l'entité souhaitée. Par exemple :

```cpp
r.addComponent<Clickable>(entity, clickComponent, scene);
```

## Exécution du Script lors d'un Clic

### Étape 1: Détecter le Clic
Le système lié au clic doit détecter un clic sur l'entité et récupérer le composant `Clickable`.

### Étape 2: Exécuter le Script
Une fois le clic détecté, le système doit exécuter le script associé :

```cpp
    r.getScript(click.script_id)(r, entity, _udp_socket, _server_endpoint);
```

## Gestion des Erreurs
- Assurez-vous de gérer `ScriptNotFoundException` si le script n'est pas trouvé.
- Vérifiez la validité de l'entité et du composant `Clickable` avant de tenter d'exécuter le script.

---

Cette documentation doit être adaptée en fonction de l'évolution du système et des besoins spécifiques de votre projet.

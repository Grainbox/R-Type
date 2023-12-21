# Documentation du Système de Connexion Client-Serveur avec ECS

## Sommaire
1. [Connexion du Client](#connexion-du-client)
2. [Traitement des Messages sur le Serveur](#traitement-des-messages-sur-le-serveur)
3. [Gestion de la Création du Jeu et Envoi d'Entités](#gestion-de-la-création-du-jeu-et-envoi-dentités)

## Connexion du Client
Lors de la connexion initiale, le client envoie un message spécifique pour établir la communication avec le serveur.

### Méthode `send_first_con`
Cette méthode est appelée pour envoyer le premier message de connexion au serveur.
```cpp
void send_first_con() {
    FirstConMessage msg;
    msg.header.type = MessageType::First_Con;

    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << msg;

    std::string serialized_str = archive_stream.str();
    _udp_socket.send_to(asio::buffer(serialized_str), _server_endpoint);
}
```

### Structures Utilisées
#### `FirstConMessage`
Structure pour le message initial de connexion.
```cpp
struct FirstConMessage {
    MessageHeader header;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
    }
};
```

#### `MessageHeader`
Contient le type de message pour faciliter le dispatching côté serveur.
```cpp
struct MessageHeader {
    MessageType type;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & type;
    }
};
```

## Traitement des Messages sur le Serveur
Le serveur reçoit et traite les messages clients dans `handle_client`.

### Fonction `handle_client`
Gère la réception des messages et appelle la fonction appropriée en fonction du type de message.
```cpp
void ServerSystem::handle_client(Registry &r, const boost::system::error_code& error, std::size_t bytes_transferred) {
    // Réception et désérialisation du message
    // Traitement du message selon son type
}
```

### Gestion de la Connexion Client (`client_connect_handler`)
```cpp
std::string ServerSystem::client_connect_handler(FirstConMessage &msg) {
    // Traite les messages de connexion client
}
```

## Gestion de la Création du Jeu et Envoi d'Entités
La fonction `create_game_handler` gère les requêtes de création de jeu et prépare l'envoi des entités ECS.

### Fonction `create_game_handler`
```cpp
std::string ServerSystem::create_game_handler(std::string message) {
    // Création de TransfertECSMessage
    // Parcours des entités et préparation pour l'envoi
}
```

### Structures Utilisées
#### `EntityComponents`
Structure représentant les composants d'une entité.
```cpp
struct EntityComponents {
    // Définition des composants
};
```

#### `TransfertECSMessage`
Structure pour le transfert des données ECS.
```cpp
struct TransfertECSMessage {
    MessageHeader header;
    std::vector<EntityComponents> entities;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
        ar & entities;
    }
};
```

### Notes
- **Composants Commentés** : Les composants non inclus actuellement seront ajoutés dans les mises à jour futures.
- **Dynamisme** : Cette approche dynamique permet une gestion efficace des entités dans le système ECS.

Pour plus d'informations sur l'interaction côté client, voir [Client Clickable Documentation](../../client/docs/Clickable.md).

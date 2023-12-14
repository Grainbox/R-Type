# Documentation sur la Sérialisation et la Désérialisation des Structures de Messages avec Boost

## Introduction
Cette documentation explique comment sérialiser et désérialiser des structures de messages en C++ en utilisant la bibliothèque Boost. Ce processus est essentiel pour la communication réseau, permettant d'envoyer et de recevoir des données structurées de manière fiable.

## Dépendances
- Boost.Serialization
- Boost.Asio (pour les exemples de sockets)

## Structures de Messages
### Définition
Les structures de messages sont définies pour encapsuler les données. Par exemple :

```cpp
enum class MessageType : uint8_t {
    First_Con = 0
};

struct MessageHeader {
    MessageType type;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & type;
    }
};

struct FirstConMessage {
    MessageHeader header;
    std::string test;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & header;
        ar & test;
    }
};
```

## Sérialisation
La sérialisation convertit les structures en un format de chaîne pour la transmission.

### Exemple de Sérialisation
```cpp
FirstConMessage msg;
msg.test = "hello";
std::ostringstream archive_stream;
boost::archive::text_oarchive archive(archive_stream);

archive << msg;

std::string serialized_str = archive_stream.str();

// Envoi via un socket UDP
_udp_socket.send_to(asio::buffer(serialized_str), _server_endpoint);
```

## Désérialisation
La désérialisation est le processus inverse, où la chaîne sérialisée est reconvertie en structure de message.

### Exemple de Désérialisation
```cpp
auto message = std::make_shared<std::string>(_recvBuffer.data(), bytes_transferred);
std::istringstream archive_stream(*message);

boost::archive::text_iarchive archive(archive_stream);
MessageHeader header;
archive >> header;

switch (header.type) {
    case MessageType::First_Con: {
        FirstConMessage msg;
        std::istringstream archive_stream(*message);
        boost::archive::text_iarchive archive(archive_stream);

        archive >> msg;  // Désérialisation
        std::cout << "Received: " << msg.test << std::endl;
        break;
    }
    default:
        std::cerr << "Type de message inconnu reçu!" << std::endl;
}
```

## Remarques
- La sérialisation et la désérialisation nécessitent que les structures de messages soient compatibles avec Boost.Serialization.
- Il est essentiel de gérer les exceptions et les erreurs potentielles lors de l'envoi et de la réception de messages.
- Boost.Asio est utilisé pour l'exemple de communication réseau, mais la sérialisation Boost peut être utilisée avec n'importe quel mécanisme de communication.

## Conclusion
La sérialisation et la désérialisation avec Boost permettent une communication réseau efficace et structurée en C++. En suivant ce guide, les développeurs peuvent implémenter un système de communication robuste pour leurs applications réseau.

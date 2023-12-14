# Documentation du Protocole de Communication en C++

## Sommaire

1. Introduction
2. Architecture du protocole
3. Structures des données
4. Sérialisation des messages
5. Désérialisation des messages
6. Gestion des erreurs
7. Exemples d'usage

## 1. Introduction

Cette documentation décrit le processus d'envoi et de récupération de messages binaires entre un client et un serveur en utilisant le langage de programmation C++. Le protocole est basé sur UDP pour un transfert rapide et non connecté.

## 2. Architecture du protocole

Le protocole définit un ensemble de messages structurés qui contiennent un en-tête commun et un corps spécifique au type de message. L'en-tête contient des informations sur le type de message pour la désérialisation correcte à la réception.

## 3. Structures des données

### En-Tête Commun

Tous les messages partagent le même en-tête pour indiquer le type de message.

```cpp
enum class MessageType : uint8_t {
    Hello = 0,
    Position = 1,
    // ... autres types de messages
};

struct MessageHeader {
    MessageType type;
};
```

### Messages Spécifiques

#### Message Hello

```cpp
struct HelloMessage {
    MessageHeader header;
    char uuid[16];
    // ... méthodes serialize et deserialize
};
```

#### Message Position

```cpp
struct PositionMessage {
    MessageHeader header;
    float x;
    float y;
    // ... méthodes serialize et deserialize
};
```

## 4. Sérialisation des messages

La sérialisation est le processus de conversion d'une structure en une séquence d'octets pour l'envoi sur le réseau.

```cpp
void serialize(const HelloMessage& msg, char* buffer) {
    std::memcpy(buffer, &msg, sizeof(HelloMessage));
}
```

## 5. Désérialisation des messages

La désérialisation est le processus inverse, où une séquence d'octets reçue est convertie en une structure.

```cpp
HelloMessage deserializeHelloMessage(const char* buffer) {
    HelloMessage msg;
    std::memcpy(&msg, buffer, sizeof(HelloMessage));
    return msg;
}
```

## 6. Gestion des erreurs

Le code doit gérer les erreurs de réseau telles que la perte de paquets, les messages corrompus et les délais d'attente.

## 7. Exemples d'usage

### Envoi d'un Message Hello

```cpp
HelloMessage helloMsg;
// ... Remplissez les données de helloMsg
char buffer[sizeof(HelloMessage)];
serialize(helloMsg, buffer);
// ... Envoyez le buffer via UDP
```

### Réception et Traitement d'un Message Hello

```cpp
char buffer[1024];
// ... Recevez les données dans le buffer
MessageType type = getMessageType(buffer);
if (type == MessageType::Hello) {
    HelloMessage helloMsg = deserializeHelloMessage(buffer);
    // ... Traitez le message Hello
}
```


```cpp
#include <cstring>
#include <cstdint>

// Continuez à utiliser l'énumération existante pour les types de messages
enum class MessageType : uint8_t {
    Hello = 0,
    Position = 1,
    // ... autres types de messages
};

// Structure de base pour un message
struct MessageHeader {
    MessageType type;
    // Ajouter d'autres champs communs à tous les messages si nécessaire
};

// Structure pour un message de position
struct PositionMessage {
    MessageHeader header; // L'en-tête avec le type de message
    float x;              // Coordonnée X
    float y;              // Coordonnée Y

    // Convertit la structure en un buffer pour l'envoi
    void serialize(char* buffer) const {
        std::memcpy(buffer, this, sizeof(PositionMessage));
    }

    // Remplit la structure à partir d'un buffer
    static PositionMessage deserialize(const char* buffer) {
        PositionMessage msg;
        std::memcpy(&msg, buffer, sizeof(PositionMessage));
        return msg;
    }
};

// Exemple d'utilisation pour sérialisation
PositionMessage posMsg;
posMsg.header.type = MessageType::Position;
posMsg.x = 100.0f; // Exemple de coordonnée X
posMsg.y = 200.0f; // Exemple de coordonnée Y

char buffer[sizeof(PositionMessage)];
posMsg.serialize(buffer);

// Envoyer buffer via UDP...

// À la réception
PositionMessage receivedPosMsg = PositionMessage::deserialize(buffer);
if (receivedPosMsg.header.type == MessageType::Position) {
    // Traiter le message Position
    float x = receivedPosMsg.x;
    float y = receivedPosMsg.y;
    // Faites quelque chose avec x et y...
}
```

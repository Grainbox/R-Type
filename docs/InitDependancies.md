# Mise en Place du Projet avec vcpkg

## Clonage du Projet

1. Clonez le projet :
   ```bash
   git clone https://github.com/EpitechPromo2026/B-CPP-500-REN-5-2-rtype-tom.daniel
   ```
2. Naviguez dans le répertoire du projet cloné :
   ```bash
   cd B-CPP-500-REN-5-2-rtype-tom.daniel
   ```

## Configuration des Sous-modules (vcpkg)

1. Initialisez et mettez à jour les sous-modules :
   ```bash
   git submodule init
   git submodule update
   ```

## Installation des Dépendances avec vcpkg

1. Naviguez dans le sous-module vcpkg :
   ```bash
   cd vcpkg
   ```
2. Configurez le binaire vcpkg :
   Windows:
   ```bash
   ./bootstrap-vcpkg.bat
   ```
   Linux:
   ```bash
   ./bootstrap-vcpkg.sh
   ```
3. Installez les dépendances nécessaires (par exemple, SFML) :
   ```bash
   ./vcpkg install sfml
   ```

## Configuration et Construction avec CMake

1. Naviguez dans le répertoire que vous voulez build (Exemple: engine):
   ```bash
   cd engine
   ```
2. Créez un répertoire de build et naviguez dedans :
   ```bash
   mkdir build && cd build
   ```
3. Configurez le projet avec CMake en spécifiant le fichier de configuration vcpkg :
   ```bash
   cmake -S .. -B .
   ```
4. Construisez le projet :
   ```bash
   cmake --build . --config Release
   ```

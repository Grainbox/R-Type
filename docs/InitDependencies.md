# Project Setup with vcpkg

This guide provides instructions on setting up the project using vcpkg to manage dependencies, specifically for C++ projects using SFML.

## Requirements

### Sur Ubuntu

Pour installer les dépendances requises sur Ubuntu, utilisez le gestionnaire de paquets `apt`. Ouvrez un terminal et exécutez les commandes suivantes :

```bash
sudo apt update
sudo apt install git libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev pkg-config autoconf automake libtool build-essential libssl-dev
```

Ces commandes mettront à jour la liste des paquets et installeront les paquets nécessaires pour votre environnement de build.

### Sur Arch Linux

Sur Arch Linux, utilisez le gestionnaire de paquets `pacman` pour installer les dépendances. Ouvrez un terminal et exécutez les commandes suivantes :

```bash
sudo pacman -Syu
sudo pacman -S git base-devel libx11 libxrandr libxcursor libxi libudev mesa pkg-config openssl
```

Ces commandes mettront à jour votre système et installeront les paquets requis. Notez que les noms de certains paquets peuvent différer de ceux d'Ubuntu.

---

Assurez-vous de vérifier la compatibilité des versions de paquets avec votre projet, car les versions peuvent varier entre les différentes distributions Linux.


## Cloning the Project

1. **Clone the project:**
   Use the following command to clone the project repository:
   ```bash
   git clone https://github.com/EpitechPromo2026/B-CPP-500-REN-5-2-rtype-tom.daniel
   ```
2. **Navigate to the cloned project directory:**
   Change to the project directory with:
   ```bash
   cd B-CPP-500-REN-5-2-rtype-tom.daniel
   ```

## Configuring Submodules (vcpkg)

1. **Initialize and update the submodules:**
   The project uses vcpkg as a submodule to manage dependencies. Initialize and update it with:
   ```bash
   git submodule init
   git submodule update
   ```

## Installing Dependencies with vcpkg

1. **Navigate to the vcpkg submodule:**
   Change to the vcpkg directory:
   ```bash
   cd vcpkg
   ```
2. **Configure the vcpkg binary:**
   - For Windows:
     ```bash
     ./bootstrap-vcpkg.bat
     ```
   - For Linux:
     ```bash
     ./bootstrap-vcpkg.sh
     ```
1. **Install the required dependencies:**
   The project requires `raylib`, `asio`, and `boost-serialization`. Install them using:
   ```bash
   ./vcpkg install raylib asio boost-serialization
   ```

### Shortcut for Windows
On Windows, you can use the provided [setup.ps1](../setup.ps1) script to automate the entire process (submodule initialization, bootstrapping, and dependency installation).

## Next Step:
- Once the dependencies are installed, proceed with building the project. Follow the instructions in [Build With CMake](BuildWithCMake.md).

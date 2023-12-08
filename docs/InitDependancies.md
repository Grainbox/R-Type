# Project Setup with vcpkg

## Cloning the Project

1. Clone the project:
   ```bash
   git clone https://github.com/EpitechPromo2026/B-CPP-500-REN-5-2-rtype-tom.daniel
   ```
2. Navigate to the cloned project directory:
   ```bash
   cd B-CPP-500-REN-5-2-rtype-tom.daniel
   ```

## Configuring Submodules (vcpkg)

1. Initialize and update the submodules:
   ```bash
   git submodule init
   git submodule update
   ```

## Installing Dependencies with vcpkg

1. Navigate to the vcpkg submodule:
   ```bash
   cd vcpkg
   ```
2. Configure the vcpkg binary:
   Windows:
   ```bash
   ./bootstrap-vcpkg.bat
   ```
   Linux:
   ```bash
   ./bootstrap-vcpkg.sh
   ```
3. Install the required dependencies (for example, SFML):
   ```bash
   ./vcpkg install sfml
   ```
4. Ajouter le path des dll à windows -- à documenter
## Next Step:
- [Build With CMake](BuildWithCMake.md)

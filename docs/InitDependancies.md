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

## Configuration and Building with CMake

1. Navigate to the directory you want to build (Example: engine):
   ```bash
   cd engine
   ```
2. Create a build directory and navigate into it:
   ```bash
   mkdir build && cd build
   ```
3. Configure the project with CMake by specifying the vcpkg configuration file:
   ```bash
   cmake -S .. -B .
   ```
4. Build the project:
   ```bash
   cmake --build . --config Release
   ```

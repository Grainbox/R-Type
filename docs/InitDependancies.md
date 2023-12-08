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

1. Setup the R_TYPE_ROOT environment variable:
   ### Linux:
   - **Temporarily**:
   ```bash
   export R_TYPE_ROOT=$(pwd)
   ```
      -  **Permanently** where .zshrc is your actual source:
   ```bash
   echo 'export R_TYPE_ROOT='$(pwd) >> ~/.zshrc
   ```
   ### Windows:

   - **Temporarily** (for the current session only):
    ```cmd
    set R_TYPE_ROOT=%cd%
    ```

   - **Permanently** (across all sessions):
        - Open the Start Search, type in "env", and choose "Edit the system environment variables".
        - In the System Properties window, click on the "Environment Variables..." button.
        - In the Environment Variables window, under "System variables" or "User variables", click "New..." to create a new variable.
        - Enter R_TYPE_ROOT for the variable name and %cd% for the variable value.
        - Click OK and apply the changes. You might need to restart your computer or log out and back in for the changes to take effect.

2. Navigate to the directory you want to build (Example: engine):
   **Note:** it could be the root of the project to build every directories.
   ```bash
   cd engine
   ```
3. Create a build directory and navigate into it:
   ```bash
   mkdir build && cd build
   ```
4. Configure the project with CMake by specifying the vcpkg configuration file:
   ```bash
   cmake -S .. -B .
   ```
5. Build the project:
   ```bash
   cmake --build . --config Release
   ```

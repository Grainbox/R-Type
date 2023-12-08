# Configuration and Building with CMake

1. Setup the R_TYPE_ROOT environment variable:
   #### Linux:
   - **Temporarily**:
   ```bash
   export R_TYPE_ROOT=$(pwd)
   ```
      -  **Permanently** where .zshrc is your actual source:
   ```bash
   echo 'export R_TYPE_ROOT='$(pwd) >> ~/.zshrc
   ```
   #### Windows:

   - **Temporarily** (for the current session only):
    ```cmd
    set R_TYPE_ROOT=%cd%
    ```

   - **Permanently** (across all sessions):
        - Open the Start Search, type in "env", and choose "Edit the system environment variables".
        - In the System Properties window, click on the "Environment Variables..." button.
        - In the Environment Variables window, under "System variables" or "User variables", click "New..." to create a new variable.
        - Enter R_TYPE_ROOT for the variable name and your project path with '/' instead of '\' for the variable value.
          - Value Exemple: "C:/Users/tagem/Documents/B-CPP-500-REN-5-2-rtype-tom.daniel"
        - Click OK and apply the changes. You might need to restart your computer or log out and back in for the changes to take effect.

2. Create a build directory and navigate into it:
   ```bash
   mkdir build && cd build
   ```
3. Configure the project with CMake by specifying the vcpkg configuration file:
   linux:
   ```bash
   cmake ..
   ```
   windows: (put you actual repo url)
   ```bash
   cmake .. -DCMAKE_PREFIX_PATH="C:\Users\tagem\Documents\B-CPP-500-REN-5-2-rtype-tom.daniel\vcpkg\installed\x64-windows\share\sfml"
   ```
4. Build the project:
   ```bash
   cmake --build .  --config Release
   ```
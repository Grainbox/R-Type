# Configuration and Building with CMake

1. Create a build directory and navigate into it:
   ```bash
   mkdir build && cd build
   ```
2. Configure the project with CMake by specifying the vcpkg configuration file:
   linux:
   ```bash
   cmake ..
   ```
   windows: (put you actual repo url)
   ```bash
   cmake .. -DCMAKE_PREFIX_PATH="repo_url\vcpkg\installed\x64-windows\share\sfml"
   ```
3. Build the project:
   ```bash
   cmake --build .  --config Release
   ```
4. Almost done, the binaries are located in (engine or client or server).

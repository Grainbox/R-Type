# Configuration and Building with CMake

## Requirements:
- CMake 3.27.2

### Automated:
Run the `build.sh` script at the root of the repository.

### Manually:

1. Create a build directory and navigate into it:
   ```bash
   mkdir build && cd build
   ```
2. Configure the project with CMake by specifying the vcpkg configuration file:
    windows:
    On Windows, it is highly recommended to use `.\setup.ps1` which handles the vcpkg toolchain integration automatically. If doing it manually:
    ```bash
    cmake .. -DCMAKE_TOOLCHAIN_FILE="..\vcpkg\scripts\buildsystems\vcpkg.cmake"
    ```
3. Build the project:
   ```bash
   cmake --build .  --config Release
   ```
4. Almost done, the binaries are located in (engine or client or server).

## Next Step:
- Once you have built your project, proceed with generating the project's documentation. Follow the instructions in [Generate Doxygen Documentation](GenerateDoxygenDocs.md).

#!/bin/bash

VCPKG_DIR="./vcpkg"

# Check if vcpkg is installed
if [ ! -d "$VCPKG_DIR" ] || [ ! -f "$VCPKG_DIR/vcpkg" ]; then
    echo "vcpkg not found in $VCPKG_DIR"
    git submodule init
    git submodule update
fi

# Check if vcpkg is initialized
if [ ! -f "$VCPKG_DIR/vcpkg" ]; then
    echo "vcpkg not initialized in $VCPKG_DIR"
    "$VCPKG_DIR/bootstrap-vcpkg.sh"
fi

# Note: Dependencies are now managed via vcpkg.json manifest mode
# vcpkg will automatically install them during CMake configuration

mkdir -p build
cd build || exit 1

# Run CMake configuration and build
echo "Configuring project..."
cmake .. -DCMAKE_TOOLCHAIN_FILE="../vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release || exit 1
echo "Building project..."
cmake --build . || exit 1

cd ..
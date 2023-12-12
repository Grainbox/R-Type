#!/bin/bash

VCPKG_DIR="./vcpkg"

# Check if vcpkg is installed
if [ ! -d "$VCPKG_DIR" ]; then
    echo "vcpkg not found in $VCPKG_DIR"
    exit 1
fi

# Install necessary libraries using vcpkg
"$VCPKG_DIR/vcpkg" install asio
"$VCPKG_DIR/vcpkg" install sfml

mkdir -p build
cd build

cmake -DCMAKE_TOOLCHAIN_FILE=".$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake" ..
cmake --build .

cd ..

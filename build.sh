#!/bin/bash

VCPKG_DIR="./vcpkg"

# Check if vcpkg is installed
if [ ! -d "$VCPKG_DIR" ]; then
    echo "vcpkg not found in $VCPKG_DIR"
    git submodules init
    git submodules update
fi

# Check if vcpkg is initialized
if [ ! "$VCPKG_DIR/vcpkg" ]; then
    echo "vcpkg not initialized in $VCPKG_DIR"
    "$VCPKG_DIR/bootstrap-vcpkg.sh"
fi

# Install necessary libraries using vcpkg
"$VCPKG_DIR/vcpkg" install asio
"$VCPKG_DIR/vcpkg" install sfml

mkdir -p build
cd build

cmake ..
cmake --build .

cd ..

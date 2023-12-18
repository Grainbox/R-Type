cmake_minimum_required(VERSION 3.27.2)
project(R-Type)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

if(APPLE)
    set(CMAKE_PREFIX_PATH "vcpkg/installed/arm64-osx")
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
    set(CMAKE_MODULE_LINKER_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
    set(CMAKE_SHARED_LINKER_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
    set(CMAKE_STATIC_LINKER_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
elseif(UNIX)
    set(CMAKE_PREFIX_PATH "vcpkg/installed/x64-linux")
elseif(WIN32)
    set(CMAKE_PREFIX_PATH "vcpkg/installed/x64-windows")
endif()

find_package(Boost COMPONENTS serialization REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(engine)
add_subdirectory(client)
add_subdirectory(server)
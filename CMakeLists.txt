cmake_minimum_required(VERSION 3.27.2)
project(R-Type)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(asio CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics network audio CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(engine)
add_subdirectory(client)
add_subdirectory(server)

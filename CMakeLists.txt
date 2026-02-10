cmake_minimum_required(VERSION 3.27.2)
project(R-Type)

# Keep old Boost find module for compatibility with vcpkg
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00) # Target Windows 10+
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-DNOGDI)
    add_definitions(-DNOUSER)
endif()

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(Boost REQUIRED COMPONENTS serialization)
find_package(asio CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(engine)
add_subdirectory(client)
add_subdirectory(server)

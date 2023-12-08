cmake_minimum_required(VERSION 3.10)

project(engine)

set(CMAKE_TOOLCHAIN_FILE ../vcpkg/scripts/buildsystems/vcpkg.cmake)

if (WIN32)
    set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/../vcpkg/installed/x64-windows/share/sfml")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

if (WIN32)
    file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/Release)
elseif (UNIX)
    file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(engine ${SOURCES})
target_link_libraries(engine PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_library(libengine SHARED ${SOURCES})
target_link_libraries(libengine sfml-graphics sfml-audio sfml-window sfml-system)

if (WIN32)
    file(GLOB_RECURSE DLL_FILES "${CMAKE_SOURCE_DIR}/../vcpkg/installed/x64-windows/bin/*.dll")
    file(COPY ${DLL_FILES} DESTINATION ${CMAKE_BINARY_DIR}/Release)
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(engine PRIVATE -Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(engine PRIVATE -Wall -Wextra)
endif()

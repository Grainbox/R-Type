cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED ENV{R_TYPE_ROOT})
    message(FATAL_ERROR "La variable d'environnement R_TYPE_ROOT n'est pas définie")
endif()

set(R_TYPE_ROOT $ENV{R_TYPE_ROOT})

project(client)

if (WIN32)
    set(CMAKE_PREFIX_PATH "${R_TYPE_ROOT}/vcpkg/installed/x64-windows")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${R_TYPE_ROOT}/client/include)

if(NOT TARGET libengine)
    add_subdirectory(${R_TYPE_ROOT}/engine engine)
endif()

if (WIN32)
	set(SFML_DIR "${R_TYPE_ROOT}/vcpkg/installed/x64-windows/share/sfml")
	find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
    	file(COPY ${R_TYPE_ROOT}/engine/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
elseif (UNIX)
    file(COPY ${R_TYPE_ROOT}/engine/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

file(GLOB_RECURSE SOURCES "${R_TYPE_ROOT}/client/src/*.cpp")
add_executable(client ${SOURCES})
target_link_libraries(client PRIVATE sfml-system sfml-network sfml-graphics sfml-window libengine)

target_include_directories(client PRIVATE ${R_TYPE_ROOT}/engine/include)

if (WIN32)
    file(GLOB_RECURSE DLL_FILES "${R_TYPE_ROOT}/vcpkg/installed/x64-windows/bin/*.dll")
    file(COPY ${DLL_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
endif()

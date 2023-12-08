cmake_minimum_required(VERSION 3.27.2)
project(R-Type)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclure les sous-répertoires
add_subdirectory(engine)
add_subdirectory(client)
add_subdirectory(server)

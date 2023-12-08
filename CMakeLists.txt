cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED ENV{R_TYPE_ROOT})
    message(FATAL_ERROR "La variable d'environnement R_TYPE_ROOT n'est pas définie")
endif()

# Nom de votre projet
project(R-Type)

# Ajouter les sous-répertoires
add_subdirectory(engine)

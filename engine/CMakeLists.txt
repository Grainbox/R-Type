add_library(engine SHARED
    src/Engine.cpp
    include/Engine.hpp
)

add_executable(engine_debug
    src/Engine.cpp
    src/main.cpp
    include/Engine.hpp
)

# Configuration commune pour les deux cibles
foreach(target engine engine_debug)
    target_include_directories(${target} PUBLIC include)

    find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
    target_link_libraries(${target} PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/engine/assets $<TARGET_FILE_DIR:${target}>/assets)
endforeach()

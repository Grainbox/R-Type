set(ENGINE_COMMON_SOURCES
    src/Engine.cpp
    src/ClientEngine.cpp
    src/ServerEngine.cpp
    include/Engine.hpp
)

add_library(engine SHARED ${ENGINE_COMMON_SOURCES})

add_executable(engine_debug ${ENGINE_COMMON_SOURCES} src/main.cpp)

foreach(target engine engine_debug)
    target_include_directories(${target} PUBLIC include)

    find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
    target_link_libraries(${target} PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

    if(UNIX)
        target_include_directories(${target} PUBLIC "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-linux/include")
    elseif(WIN32)
        target_include_directories(${target} PUBLIC "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/include")
    endif()

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/engine/assets $<TARGET_FILE_DIR:${target}>/assets)
endforeach()


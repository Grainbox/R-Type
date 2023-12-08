add_executable(server)
target_sources(server PRIVATE
    src/main.cpp
)

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

target_include_directories(server PUBLIC include)
target_link_libraries(server PRIVATE engine sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/engine/assets $<TARGET_FILE_DIR:server>/assets)

if (WIN32)
add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_BINARY_DIR}/engine/Release/engine.dll $<TARGET_FILE_DIR:server>)
endif()

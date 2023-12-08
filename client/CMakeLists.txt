add_executable(client)
target_sources(client PRIVATE
    src/main.cpp
)

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

target_include_directories(client PUBLIC include)
target_link_libraries(client PRIVATE engine sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/engine/assets $<TARGET_FILE_DIR:client>/assets)

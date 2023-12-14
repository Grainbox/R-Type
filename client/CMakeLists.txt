add_executable(client)
target_sources(client PRIVATE
    src/main.cpp
)

target_include_directories(client PUBLIC include)
target_link_libraries(client PRIVATE engine raylib)

add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/engine/assets $<TARGET_FILE_DIR:client>/assets)

if (WIN32)
add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_BINARY_DIR}/engine/Release/engine.dll $<TARGET_FILE_DIR:client>)
endif()

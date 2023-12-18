add_executable(r-type_client)
target_sources(r-type_client PRIVATE
    src/main.cpp
)

target_include_directories(r-type_client PUBLIC include)
target_link_libraries(r-type_client PRIVATE engine raylib)

add_custom_command(TARGET r-type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/engine/assets $<TARGET_FILE_DIR:r-type_client>/assets)

if (WIN32)
add_custom_command(TARGET r-type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_BINARY_DIR}/engine/Release/engine.dll $<TARGET_FILE_DIR:r-type_client>)
endif()

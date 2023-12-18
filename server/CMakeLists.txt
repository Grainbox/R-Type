add_executable(r-type_server)
target_sources(r-type_server PRIVATE
    src/main.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

target_include_directories(r-type_server PUBLIC include)
target_link_libraries(r-type_server PRIVATE engine raylib)

add_custom_command(TARGET r-type_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/engine/assets $<TARGET_FILE_DIR:r-type_server>/assets)

if (WIN32)
add_custom_command(TARGET r-type_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_BINARY_DIR}/engine/Release/engine.dll $<TARGET_FILE_DIR:r-type_server>)
endif()

set(ENGINE_SOURCES
    src/Engine.cpp
    src/ClientEngine.cpp
    src/ServerEngine.cpp
)

add_library(engine SHARED ${ENGINE_SOURCES})

target_include_directories(engine PUBLIC include)
target_link_libraries(engine PRIVATE raylib Boost::boost Boost::serialization)

add_custom_command(TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/engine/assets $<TARGET_FILE_DIR:engine>/assets)

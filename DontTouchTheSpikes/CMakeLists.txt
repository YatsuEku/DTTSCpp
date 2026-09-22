find_package(SFML 3 CONFIG REQUIRED COMPONENTS Graphics Audio)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(
    DontTouchTheSpikes
    ${GAME_SOURCES})

target_include_directories(
    DontTouchTheSpikes
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(
    DontTouchTheSpikes
    PRIVATE
        SFML::Graphics
        SFML::Audio
)

target_compile_features(
    DontTouchTheSpikes
    PRIVATE
        cxx_std_23
)

add_custom_command(
        TARGET DontTouchTheSpikes POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:DontTouchTheSpikes>/assets"
)
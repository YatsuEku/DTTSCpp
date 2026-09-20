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
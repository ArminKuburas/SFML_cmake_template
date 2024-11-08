cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp src/TicTacToe.cpp)
target_link_libraries(main PRIVATE sfml-graphics sfml-audio)
target_compile_features(main PRIVATE cxx_std_17)

# Ensure the resources/sounds directory is created
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:main>/resources
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:main>/resources/sounds
	COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:main>/resources/fonts
)

# Copy resources to the output directory
file(GLOB SOUND_FILES "${CMAKE_SOURCE_DIR}/resources/sounds/*")
foreach(SOUND_FILE ${SOUND_FILES})
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SOUND_FILE} $<TARGET_FILE_DIR:main>/resources/sounds
    )
endforeach()

file(GLOB FONT_FILES "${CMAKE_SOURCE_DIR}/resources/fonts/*")
foreach(FONT_FILE ${FONT_FILES})
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${FONT_FILE} $<TARGET_FILE_DIR:main>/resources/fonts
    )
endforeach()

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()

cmake_minimum_required(VERSION 3.28)
project(MandelbrotSet LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ASSET_DIRS "fonts")

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(MandelbrotSet main.cpp
        main.cpp)
target_compile_features(MandelbrotSet PRIVATE cxx_std_17)
target_link_libraries(MandelbrotSet PRIVATE sfml-graphics sfml-audio sfml-window)

foreach(DIR ${ASSET_DIRS})
    add_custom_command(TARGET MandelbrotSet POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}"
            "${CMAKE_BINARY_DIR}/bin/${DIR}"
    )
endforeach()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MandelbrotSet)
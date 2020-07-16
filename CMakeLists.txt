cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(APP_NAME Backing)
set(BINARY_NAME backing)
set(PROJECT_DESCRIPTION "Application to mock your back-end for front-end testing")
set(PROJECT_URI "https://backing.bartkessels.net")
set(VER_MAJOR 0)
set(VER_MINOR 0)
set(VER_PATCH 1)

project(${APP_NAME}
    VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    HOMEPAGE_URL "https://github.com/bartkessels/backing"
)

# Variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_XX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build)

# Subdirectories
add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(packaging)

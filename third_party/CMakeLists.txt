cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

include(FetchContent)

# ------------------------------------------------------------------------------
# Catch2
FetchContent_Declare(
    catch2

    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.12.2)
FetchContent_MakeAvailable(catch2)

# ------------------------------------------------------------------------------
# Cpp rest SDK
FetchContent_Declare(
        cpprest

        GIT_REPOSITORY https://github.com/microsoft/cpprestsdk.git
        GIT_TAG        v2.10.16)
set(cpprest_BUILD_TESTS OFF)
set(cpprest_BUILD_SAMPLES OFF)
set(BUILD_TESTS OFF)
set(BUILD_SAMPLES OFF)
FetchContent_MakeAvailable(cpprest)
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

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
set(cpprest_BUILD_TESTS 0)
set(cpprest_BUILD_SAMPLES 0)
set(BUILD_TESTS 0)
set(BUILD_SAMPLES 0)
FetchContent_MakeAvailable(cpprest)
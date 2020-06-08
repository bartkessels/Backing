cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

include(FetchContent)

# ------------------------------------------------------------------------------
# Catch2
FetchContent_Declare(
    extern_catch2

    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.12.2)
FetchContent_MakeAvailable(extern_catch2)

# ------------------------------------------------------------------------------
# Cpp rest SDK
FetchContent_Declare(
        extern_restsdk

        GIT_REPOSITORY https://github.com/microsoft/cpprestsdk.git
        GIT_TAG        v2.10.16)
FetchContent_MakeAvailable(extern_restsdk)
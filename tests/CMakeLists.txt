cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

find_package(Boost COMPONENTS thread system chrono REQUIRED)

set(SRCFILES
        ../src/domain/exception/InvalidUriException.hpp
        ../src/domain/exception/ListenerAlreadyStartedException.hpp
        ../src/domain/exception/MethodNotRegisteredException.hpp
        ../src/domain/CppRestRequestListener.cpp
        ../src/domain/Listener.cpp
        ../src/domain/ListenerFactory.cpp
        ../src/domain/Response.hpp
)

set(TST_SRCFILES
        domain/exception/tst_InvalidUriException.cpp
        domain/exception/tst_ListenerAlreadyStartedException.cpp
        domain/exception/tst_MethodNotRegisteredException.cpp
        domain/tst_CppRestRequestListener.cpp
        domain/tst_Listener.cpp
        domain/tst_ListenerFactory.cpp
        domain/tst_Response.cpp

        mocks/MockLogger.hpp

        main.cpp
)

add_executable(backing_tests ${SRCFILES} ${TST_SRCFILES})

# Include directories for dependencies
include_directories(../src)

# Libraries
target_link_libraries(backing_tests Boost::system)
target_link_libraries(backing_tests cpprest)
target_link_libraries(backing_tests Catch2::Catch2)

enable_testing()
add_test(NAME backing_tests COMMAND backing_tests)
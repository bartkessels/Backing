cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
set(LIBRARIES Boost::system cpprest Qt5::Widgets)

set(CMAKE_CXX_STANDARD 20)

set(SOURCEFILES
        domain/CppRestRequestListener.cpp
        domain/Listener.cpp
        domain/ListenerFactory.cpp
        domain/QtLogger.cpp

        gui/MainWindow/MainWindow.cpp
        gui/widget/LoggingWidget/LoggingWidget.cpp
        gui/widget/MethodWidget/MethodWidget.cpp

        main.cpp
)

set(HEADERFILES
        domain/exception/InvalidUriException.hpp
        domain/exception/ListenerAlreadyStartedException.hpp
        domain/exception/ListenerNotStartedException.hpp
        domain/exception/MethodNotRegisteredException.hpp
        domain/CppRestRequestListener.hpp
        domain/Listener.hpp
        domain/ListenerFactory.hpp
        domain/Logger.hpp
        domain/Response.hpp
        domain/QtLogger.hpp

        gui/MainWindow/MainWindow.hpp
        gui/widget/LoggingWidget/LoggingWidget.hpp
        gui/widget/MethodWidget/MethodWidget.hpp
)

add_executable(
        ${BINARY_NAME}
        ${HEADERFILES}
        ${SOURCEFILES}
        ../resources/resources.qrc
)

install(TARGETS ${BINARY_NAME}
        RUNTIME
        DESTINATION
)

# Libraries
target_link_libraries(${BINARY_NAME} ${LIBRARIES})

if (APPLE)
    add_custom_command(
            TARGET ${BINARY_NAME}
            POST_BUILD
            COMMAND macdeployqt bin/${BINARY_NAME}.app
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
elseif (WIN32)
    add_custom_command(
            TARGET ${BINARY_NAME}
            POST_BUILD
            COMMAND windeployqt.exe bin/Release/${BINARY_NAME}.exe
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif ()

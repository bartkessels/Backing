cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(SOURCEFILES
        domain/CppRestRequestListener.cpp
        domain/RequestListener.cpp
        domain/RequestListenerFactory.cpp

        gui/MainWindow/MainWindow.cpp
        gui/widget/LoggingWidget/LoggingWidget.cpp
        gui/widget/RequestListenerWidget/RequestListenerWidget.cpp

        main.cpp
)

set(HEADERFILES
        domain/exception/InvalidRequestException.hpp
        domain/exception/InvalidResponseException.hpp
        domain/exception/ListenerAlreadyClosedException.hpp
        domain/exception/ListenerAlreadyStartedException.hpp
        domain/CppRestRequestListener.hpp
        domain/Logger.hpp
        domain/Request.hpp
        domain/RequestListener.hpp
        domain/RequestListenerFactory.hpp
        domain/Response.hpp

        gui/MainWindow/MainWindow.hpp
        gui/widget/LoggingWidget/LoggingWidget.hpp
        gui/widget/RequestListenerWidget/RequestListenerWidget.hpp
)

add_executable(
        backing
        ${HEADERFILES}
        ${SOURCEFILES}
        ../resources/resources.qrc
)

# Libraries
target_link_libraries(backing Boost::system)
target_link_libraries(backing cpprest)
target_link_libraries(backing Qt5::Widgets)

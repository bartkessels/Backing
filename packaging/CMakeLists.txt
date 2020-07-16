cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CPACK_PACKAGE_NAME ${APP_NAME})
set(CPACK_PACKAGE_VENDOR "Bart Kessels")
set(CPACK_PACKAGE_VERSION_MAJOR ${VER_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VER_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VER_PATCH})
set(CPACK_PACKAGE_ICON ../resources/icons/main.svg)

if (WIN32)
    set(COMPLETE_BINARY_NAME Release/backing.exe)
elseif (APPLE)
    set_target_properties(${BINARY_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
    set_target_properties(
        ${BINARY_NAME}
        PROPERTIES
        RESOURCE "macos/icons/backing.icns"
    )

    set(COMPLETE_BINARY_NAME backing.app)

    set(CPACK_BUNDLE_NAME Backing)
    set(CPACK_BUNDLE_PLIST macos/Info.plist)
    set(CPACK_BUNDLE_ICON macos/icons/backing.icns)
    set(CPACK_PRODUCTBUILD_RESOURCES_DIR macos)

    set(MACOSX_FRAMEWORK_ICON_FILE macos/icons/backing.icns)
    set(MACOSX_FRAMEWORK_IDENTIFIER net.bartkessels.backing)
elseif (UNIX AND NOT APPLE)
    set(COMPLETE_BINARY_NAME backing)
endif()

install(TARGETS ${APP_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${COMPLETE_BINARY_NAME})
set(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/build/bin/${COMPLETE_BINARY_NAME};${APP_NAME};ALL;/")

include(CPack)

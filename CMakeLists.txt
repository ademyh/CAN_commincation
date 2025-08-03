cmake_minimum_required(VERSION 3.19)
project(untitled LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(untitled
    WIN32 MACOSX_BUNDLE
    main.cpp
    senderwindow.cpp
    senderwindow.h
    senderwindow.ui
    receiverwindow.h receiverwindow.cpp receiverwindow.ui
    canmessage.h canmessage.cpp
    homewindow.h homewindow.cpp homewindow.ui
    canreceiver.h canreceiver.cpp
    photo.qrc
    proj.qrc
)

target_link_libraries(untitled
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(untitled PRIVATE Qt6::Core)

include(GNUInstallDirs)

install(TARGETS untitled
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET untitled
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

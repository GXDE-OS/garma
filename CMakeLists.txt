cmake_minimum_required(VERSION 3.14)
project(garma VERSION 1.2.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets DBus)
find_package(PkgConfig REQUIRED)

pkg_check_modules(DTK2WIDGET REQUIRED IMPORTED_TARGET dtk2widget)

set(SOURCES
    main.cpp
    Garma.cpp
    dialogmanager.cpp
    gmessagebox.cpp
    gprogressdialog.cpp
)

set(HEADERS
    Garma.h
    define_global.h
    dialogmanager.h
    gmessagebox.h
    gprogressdialog.h
    inputguard.h
)

set(RESOURCES
    images.qrc
)

add_executable(garma ${SOURCES} ${HEADERS} ${RESOURCES})

target_include_directories(garma PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(garma PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::DBus
    PkgConfig::DTK2WIDGET
    X11
)

target_compile_definitions(garma PRIVATE WS_X11)

if(NOT DEFINED CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX /usr)
endif()

install(TARGETS garma DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY translations/
    DESTINATION share/garma/translations
    FILES_MATCHING PATTERN "*.qm"
)

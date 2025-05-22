cmake_minimum_required(VERSION 3.16)
project(HLib LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QuaZip-Qt6)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql)
qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(HLib
    src/db/dbmanager.cpp
    src/db/dbmanager.h
    src/gui/imageview.cpp
    src/gui/imageview.h
    src/gui/logwindow.cpp
    src/gui/logwindow.h
    src/gui/mainwindow.cpp
    src/gui/mainwindow.h
    src/main.cpp
    src/utils/logging.cpp
    src/utils/logging.h
    src/utils/utildefs.h
    src/utils/utilfuncs.cpp
    src/utils/utilfuncs.h
)

target_sources(HLib
    PRIVATE
        src/gui/ui/logwindow.ui
        src/gui/ui/mainwindow.ui
)

qt_add_resources(HLib_resources src/gui/theme/darkthemes.qrc)
target_sources(HLib
    PRIVATE
        ${HLib_resources}
)

target_include_directories(HLib PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(HLib
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        QuaZip::QuaZip
)


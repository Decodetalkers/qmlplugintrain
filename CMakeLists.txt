cmake_minimum_required(VERSION 3.16)

project(qmlpluginstrain
    VERSION 0.1
    LANGUAGES CXX
)

set(QT_VERSION "5" CACHE STRING "Qt Version")
# TODO: 6

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt${QT_VERSION} COMPONENTS Quick Widgets QuickControls2 REQUIRED)
find_package(Dtk COMPONENTS Core Gui)
find_package(DtkDeclarative REQUIRED)
file(GLOB_RECURSE Interface_SRCS
    "./include/interface/*.h"
)

add_library(qmlpluginstrainInterface SHARED
    ${Interface_SRCS}
    src/interface/modulemodel.cpp
)

target_include_directories(qmlpluginstrainInterface PUBLIC
    include/interface
)


target_link_libraries(qmlpluginstrainInterface
    PUBLIC
    Qt::Quick
    Qt::Widgets
    Qt::QuickControls2
)

if (QT_VERSION STREQUAL "6")
    qt_add_executable(${PROJECT_NAME}
        src/frame/main.cpp
        src/frame/PluginLoader.h
        src/frame/PluginLoader.cpp
        ${Interface_SRCS}
    )

    # Not Format Me
    qt_add_qml_module(${PROJECT_NAME}
        URI Marine
        VERSION 1.0
        QML_FILES
            ./qml/main.qml
            ./qml/VListView.qml
            ./qml/PageLoaderV.qml
            ./qml/HListView.qml
            ./qml/PageLoaderH.qml
    )
else()
    add_executable(${PROJECT_NAME}
        src/frame/main.cpp
        src/frame/PluginLoader.h
        src/frame/PluginLoader.cpp
        ${Interface_SRCS}
        qml/source.qrc
        misc/icons.qrc
    )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    include/interface
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt::Quick
    Qt::Widgets
    Qt::QuickControls2
    Dtk::Gui
    Dtk::Core
    ${DtkDeclarative_LIBRARIES}
    qmlpluginstrainInterface
)



add_subdirectory(pluginexamples/plugina)
add_subdirectory(pluginexamples/pluginb)
add_subdirectory(pluginexamples/pluginc)
add_subdirectory(pluginexamples/plugind)
add_subdirectory(pluginexamples/plugine)

add_subdirectory(oldpluginloader)

add_subdirectory(coreplugins/plugin-systeminfo)

add_subdirectory(plugins/Marine/Model)

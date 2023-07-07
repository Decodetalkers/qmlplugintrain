cmake_minimum_required(VERSION 3.16)

project(qmlpluginstrain
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Quick Widgets QuickControls2 REQUIRED)

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
    Qt6::Quick
    Qt6::Widgets
    Qt6::QuickControls2

)

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
        ./qml/PageLoader.qml
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include/interface
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt6::Quick
    Qt6::Widgets
    Qt6::QuickControls2
    qmlpluginstrainInterface
)



add_subdirectory(plugins/plugina)
add_subdirectory(plugins/pluginb)

set(LIBNAME plugin-systeminfo)

find_package(Qt${QT_VERSION} COMPONENTS Quick Widgets QuickControls2 REQUIRED)

find_package(Dtk COMPONENTS Core)

find_package(DtkDeclarative REQUIRED)

add_library(${LIBNAME} SHARED
    systeminfoplugin.h
    systeminfoplugin.cpp
    AboutMyPcBackendObject.h
    AboutMyPcBackendObject.cpp
    LicencesBackendObject.h
    LicencesBackendObject.cpp
    quicksource.qrc
    qrc/systeminfo.qrc
)

target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../include/interface
)

target_link_libraries(${LIBNAME} PUBLIC
    Qt::Quick
    Qt::Widgets
    Qt::QuickControls2
    Dtk::Core
    qmlpluginstrainInterface
    ${DtkDeclarative_LIBRARIES}
)

set_target_properties(${LIBNAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "$<TARGET_FILE_DIR:qmlpluginstrain>/pluginexamples"
)

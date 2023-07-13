set(LIBNAME pluginb)

find_package(Qt${QT_VERSION} COMPONENTS Quick Widgets QuickControls2 REQUIRED)

add_library(${LIBNAME} SHARED
    pluginb.h
    pluginb.cpp
    GlobalConst.h
    GlobalConst.cpp
    source.qrc
)

target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../include/interface
)

target_link_libraries(${LIBNAME} PUBLIC
    Qt::Quick
    Qt::Widgets
    Qt::QuickControls2
    qmlpluginstrainInterface
)

set_target_properties(${LIBNAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "$<TARGET_FILE_DIR:qmlpluginstrain>/pluginexamples"
)

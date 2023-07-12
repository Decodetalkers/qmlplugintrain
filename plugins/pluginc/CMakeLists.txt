set(LIBNAME pluginc)

find_package(Qt${QT_VERSION} COMPONENTS Quick Widgets QuickControls2 REQUIRED)

add_library(${LIBNAME} SHARED
    pluginc.h
    pluginc.cpp
)

target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../include/interface
)

target_link_libraries(${LIBNAME} PUBLIC
    Qt::Quick
    Qt::Widgets
    Qt::QuickControls2
)

set_target_properties(${LIBNAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "$<TARGET_FILE_DIR:qmlpluginstrain>/plugins"
)

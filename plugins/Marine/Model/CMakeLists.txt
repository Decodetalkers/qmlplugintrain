set(LIBNAME qmlpluginstrainplugin)

find_package(Qt${QT_VERSION} COMPONENTS Quick Widgets QuickControls2 REQUIRED)

add_library(${LIBNAME} SHARED
    dccPlugin.h
    dccPlugin.cpp
    qmldir
)
target_link_libraries(${LIBNAME}
    PUBLIC
    Qt::Quick
    Qt::Widgets
    Qt::QuickControls2
)

target_include_directories(${LIBNAME} PUBLIC
    ../../../include/interface
)

# Not Format Me
add_custom_command(
    TARGET ${LIBNAME}
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_LIST_DIR}/qmldir
        $<TARGET_FILE_DIR:qmlpluginstrainplugin>/qmldir
)

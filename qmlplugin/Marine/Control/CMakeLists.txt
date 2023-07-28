set(LIBNAME qmlpluginstrainplugin)

find_package(Qt${QT_VERSION} COMPONENTS Quick Widgets QuickControls2 REQUIRED)
find_package(DtkDeclarative REQUIRED)

add_library(${LIBNAME} SHARED
    dccPlugin.h
    dccPlugin.cpp
    qmldir
    source.qrc
)

target_link_libraries(${LIBNAME}
    PUBLIC
    Qt::Quick
    Qt::Widgets
    Qt::QuickControls2
    ${DtkDeclarative_LIBRARIES}
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

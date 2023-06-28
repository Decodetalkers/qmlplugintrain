set(LIBNAME plugina)

find_package(Qt6 COMPONENTS Quick Widgets QuickControls2 REQUIRED)

add_library(${LIBNAME} SHARED
    plugina.h
    plugina.cpp
)

target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../include/interface
)

target_link_libraries(${LIBNAME} PUBLIC
    Qt6::Quick
    Qt6::Widgets
    Qt6::QuickControls2
)

set_target_properties(${LIBNAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "$<TARGET_FILE_DIR:qmlpluginstrain>/plugins"
)

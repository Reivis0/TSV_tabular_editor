set(CMAKE_AUTORCC ON)

set(SOURCES
    main.cpp
    mainwindow.cpp
    mytablemodel.cpp
)


set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mytablemodel.h
)

add_executable(tsv-editor ${SOURCES} ${HEADERS})

target_include_directories(tsv-editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(tsv-editor Qt5::Core Qt5::Widgets)

set_target_properties(tsv-editor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
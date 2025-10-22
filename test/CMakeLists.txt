set(CMAKE_AUTOMOC ON)

add_executable(test-tsv-editor
    tests.cpp
    ${CMAKE_SOURCE_DIR}/src/tsv-editor/mytablemodel.cpp
    ${CMAKE_SOURCE_DIR}/src/tsv-editor/mainwindow.cpp)

target_sources(test-tsv-editor PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/tsv-editor/include/mytablemodel.h
    ${CMAKE_SOURCE_DIR}/src/tsv-editor/include/mainwindow.h)


target_link_libraries(test-tsv-editor
    GTest::GTest 
    GTest::Main
    Qt5::Core
    Qt5::Widgets
)


add_test(NAME tsv-editor-tests COMMAND test-tsv-editor)

target_compile_definitions(test-tsv-editor PRIVATE TEST_MODE=1)
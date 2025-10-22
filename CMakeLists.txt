cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(tsv-editor VERSION 1.0.0 DESCRIPTION "Табличный редактор TSV")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(GTest REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/src/tsv-editor/include)
add_subdirectory(src/tsv-editor)

enable_testing()
add_subdirectory(test)
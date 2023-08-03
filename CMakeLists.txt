cmake_minimum_required(VERSION 3.16)
project(MyQtApplication)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt4 REQUIRED QtGui QtCore)
include(${QT_USE_FILE})

# assuming the .cpp and .h files are in the 'src' directory
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.h)

# Add the main.cpp and mainwindow.cpp file from the root directory of your project
list(APPEND SOURCES main.cpp mainwindow.cpp maingamescreen.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt4::QtGui Qt4::QtCore)


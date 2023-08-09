cmake_minimum_required(VERSION 3.16)
project(OnlineRamseyGame)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt4 REQUIRED QtGui QtCore)
include(${QT_USE_FILE})
find_package(Boost 1.82.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.h)

list(APPEND SOURCES main.cpp mainwindow.cpp maingamescreen.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt4::QtGui Qt4::QtCore ${Boost_LIBRARIES})


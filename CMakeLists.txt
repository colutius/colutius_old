cmake_minimum_required(VERSION 3.19)
project(colutius)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Network)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)

add_executable(${PROJECT_NAME}
        src/main.cc
        src/server.hh
        src/server.cc
        src/socket.hh
        src/socket.cc

        src/ui/mainwidget.hh
        src/ui/mainwidget.cc
        src/ui/mainwidget.ui
        src/ui/loginwidget.hh
        src/ui/loginwidget.cc
        src/ui/loginwidget.ui
        src/ui/config.hh
        src/ui/config.cc
        src/ui/config.ui

        src/resource/resource.qrc
        src/resource/img/logo.rc
        )

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

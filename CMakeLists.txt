cmake_minimum_required(VERSION 3.20)
project(readsProfiler)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(dependencies/CDS/include)
include_directories(dependencies)
include_directories(common)

add_executable(client
        client/mainwindow.cpp
        client/mainwindow.h
        client/client.cpp
        client/Filter.cpp
        client/Filter.h
        client/AbstractDrawable.h
        dependencies/include.h
        client/Genre.cpp
        client/Genre.h
        client/LibraryTable.cpp
        client/LibraryTable.h
        client/LoginWindow.cpp
        client/LoginWindow.h
        common/Socket.h client/RequestHandler.cpp client/RequestHandler.h client/readWindow.cpp client/readWindow.h)

add_executable(server
        server/Server.cpp
        server/Server.h
        common/Socket.h server/ClientThread.cpp server/ClientThread.h)

add_executable(test
        client/dummyClient.cpp
        common/Socket.h
        dependencies/include.h
        )

set(CMAKE_PREFIX_PATH "~/Qt/6.1.2/gcc_64")
set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)



target_link_libraries(client ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(server ${REQUIRED_LIBS_QUALIFIED} pthread)
target_link_libraries(test ${REQUIRED_LIBS_QUALIFIED})

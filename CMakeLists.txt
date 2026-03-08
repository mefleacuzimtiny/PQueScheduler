cmake_minimum_required(VERSION 3.16)

project(PQueScheduler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PQueScheduler main.cpp
    scheduler.h scheduler.cpp
    queue.h queue.cpp
    prtqueue.h prtqueue.cpp
    process.h process.cpp)

include(GNUInstallDirs)
install(TARGETS PQueScheduler
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

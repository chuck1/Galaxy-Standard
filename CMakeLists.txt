CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

PROJECT(Galaxy-Standard)

FIND_PACKAGE(CMakeHelper)

INCLUDE(${CMakeHelper_INCLUDE_DIR}/CMakeHelper/static/library.cmake)

cmh_static_library()

ADD_SUBDIRECTORY(test)


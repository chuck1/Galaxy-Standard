CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

PROJECT(Galaxy-Standard)

FIND_PACKAGE(CMakeHelper)

SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_NO_SYSTEM_PATHS ON)
SET(BOOST_ROOT /scratch/usr)

FIND_PACKAGE(Boost 1.55 COMPONENTS
	system
	thread
	program_options
	python
	REQUIRED)

INCLUDE_DIRECTORIES("/usr/include/python2.7")

MESSAGE(STATUS "boost: ${Boost_SYSTEM_LIBRARY}")

SET(libs
	Galaxy-Standard
	${Boost_LIBRARIES}
	pthread
	python2.7
	rt
	dl
	)


cmh_static_library()

ADD_SUBDIRECTORY(test)

